#include <iostream>
#include <fstream>
#include <print>
#include <random>
#include <filesystem>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <omp.h>
#include <chrono>

#include "config.h"
#include "statistics.h"
#include "shapes.h"

namespace fs = std::filesystem;

std::vector<Point> loadCSV(const std::string& filename) {
    std::vector<Point> cloud;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::println(stderr, "Fehler: Konnte Datei '{}' nicht finden!", filename);
        std::println(stderr, "Aktuelles Verzeichnis: {}", std::filesystem::current_path().string());
        return {};
    }

    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string x_str, y_str;

        if (std::getline(ss, x_str, ',') && std::getline(ss, y_str, ',')) {
            try {
                cloud.push_back({std::stod(x_str), std::stod(y_str)});
            } catch (...) {
                continue;
            }
        }
    }
    return cloud;
}

// Prüft, ob die neuen Statistiken innerhalb der erlaubten Toleranz liegen
bool checkStats(const DatasetStats& base, const DatasetStats& current) {

    return std::abs(base.mean_x - current.mean_x) < Config::EPSILON &&
           std::abs(base.mean_y - current.mean_y) < Config::EPSILON &&
           std::abs(base.std_x - current.std_x) < Config::EPSILON &&
           std::abs(base.std_y - current.std_y) < Config::EPSILON &&
           std::abs(base.correlation - current.correlation) < Config::EPSILON;
}

// Verschiebt einen zufälligen Punkt in der Cloud um ein kleines Stück
void perturbPoint(std::vector<Point>& points, size_t idx, std::mt19937& gen, double temp) {
    // Die Schrittweite sinkt mit der Temperatur
    // Start bei ca. 1.0 und geht runter bis 0.01
    double amplitude = std::max(Config::MIN_AMPLITUDE, temp * Config::AMPLITUDE_FACTOR);
    std::uniform_real_distribution<double> moveDist(-amplitude, amplitude);

    points[idx].x += moveDist(gen);
    points[idx].y += moveDist(gen);
}

void saveCSV(const std::vector<Point>& points, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::println(stderr, "Fehler: Konnte Export-Datei {} nicht erstellen!", filename);
        return;
    }

    // Hohe Präzision ist zwingend, da die Distanzen im Feintuning marginal sind
    for (const auto& p : points) {
        file << std::fixed << std::setprecision(6) << p.x << "," << p.y << "\n";
    }

    std::println("Ergebnis erfolgreich nach '{}' exportiert.", filename);
}

double runOptimization(std::vector<Point>& points,
                     const TargetShape& target,
                     const DatasetStats& baseline,
                     const std::string& frameDir,
                     int chainID,
                     bool saveTimeline) {

    // Einzigartiger Seed pro Thread, um identische Abläufe zu verhindern
    std::mt19937 gen(std::random_device{}() + chainID);
    std::uniform_real_distribution<double> unitDist(0.0, 1.0);
    std::uniform_int_distribution<size_t> indexDist(0, points.size() - 1);

    double temp = Config::START_TEMP;
    const double n = static_cast<double>(points.size());

    // Initiale Summen berechnen (O(N) - nur einmal beim Start)
    double sX = 0, sY = 0, sX2 = 0, sY2 = 0, sXY = 0;
    double currentEnergy = 0;
    for (const auto& p : points) {
        sX += p.x; sY += p.y;
        sX2 += p.x * p.x; sY2 += p.y * p.y;
        sXY += p.x * p.y;
        currentEnergy += target.distanceTo(p);
    }

    for (int i = 0; i < Config::TOTAL_ITERATIONS; ++i) {
        size_t idx = indexDist(gen);
        Point oldP = points[idx];
        double oldDist = target.distanceTo(oldP);

        perturbPoint(points, idx, gen, temp);
        Point newP = points[idx];

        // PERFORMANCE-CORE: Inkrementelles Update in O(1)
        // Statt O(N) bei jedem der Milliarden Schritte die komplette Varianz neu zu berechnen,
        // subtrahieren wir lediglich den alten Zustand und addieren den neuen.
        double nextSX = sX - oldP.x + newP.x;
        double nextSY = sY - oldP.y + newP.y;
        double nextSX2 = sX2 - (oldP.x * oldP.x) + (newP.x * newP.x);
        double nextSY2 = sY2 - (oldP.y * oldP.y) + (newP.y * newP.y);
        double nextSXY = sXY - (oldP.x * oldP.y) + (newP.x * newP.y);

        DatasetStats nextStats;
        nextStats.mean_x = nextSX / n;
        nextStats.mean_y = nextSY / n;
        double varX = (nextSX2 - (nextSX * nextSX) / n) / (n - 1);
        double varY = (nextSY2 - (nextSY * nextSY) / n) / (n - 1);
        nextStats.std_x = std::sqrt(std::max(0.0, varX));
        nextStats.std_y = std::sqrt(std::max(0.0, varY));
        double cov = (nextSXY - (nextSX * nextSY) / n) / (n - 1);
        nextStats.correlation = (nextStats.std_x > 0 && nextStats.std_y > 0)
                                ? cov / (nextStats.std_x * nextStats.std_y) : 0;

        // Statistische Randbedingungen prüfen
        if (checkStats(baseline, nextStats)) {
            double newDist = target.distanceTo(newP);
            double deltaE = newDist - oldDist;

            // Metropolis-Kriterium (Simulated Annealing)
            // Erlaubt gelegentlich Verschlechterungen (deltaE > 0), um lokale Minima zu verlassen.
            if (deltaE < 0 || (temp > 0.000001 && unitDist(gen) < std::exp(-deltaE / temp))) {
                // Akzeptiert
                currentEnergy += deltaE;
                sX = nextSX; sY = nextSY; sX2 = nextSX2; sY2 = nextSY2; sXY = nextSXY;
            } else {
                points[idx] = oldP; // Rückgängig (zu viel Energie)
            }
        } else {
            points[idx] = oldP; // Rückgängig (Statistik verletzt)
        }

        // Export der Zwischenschritte für Videos
        if (chainID == 0 && saveTimeline) {
            bool takeSnapshot = false;

            if (i < 10'000'000) {
                if (i % 100'000 == 0) takeSnapshot = true;
            }
            else if (i < 100'000'000) {
                if (i % 1'000'000 == 0) takeSnapshot = true;
            }
            else {
                if (i % 10'000'000 == 0) takeSnapshot = true;
            }

            if (takeSnapshot) {
                std::string filename = std::format("{}/frame_{:010d}.csv", frameDir, i);
                saveCSV(points, filename);
            }
        }

        temp *= Config::COOLING_RATE;
    }

    if (chainID == 0) {
        saveCSV(points, frameDir + "/frame_final.csv");
    }

    return currentEnergy;
}

void printHelp(const char* progName) {
    std::println("Nutzung: {} [OPTIONEN] <input.csv> <target.csv>", progName);
    std::println("Optionen:");
    std::println("  -h, --help      Zeigt diese Hilfe an");
    std::println("  -t, --timeline  Speichert Zwischenschritte (Zeitstrahl) ab");
    std::println("\nBeispiel:");
    std::println("  {} --timeline data/dino.csv data/circle.csv", progName);
}

int main(int argc, char* argv[]) {
    std::vector<std::string> csvFiles;
    bool saveTimeline = false;

    // Kommandozeilen-Parser
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            printHelp(argv[0]);
            return 0;
        }
        else if (arg == "-t" || arg == "--timeline") {
            saveTimeline = true;
        }
        else if (arg.length() >= 4 && arg.substr(arg.length() - 4) == ".csv") {
            csvFiles.push_back(arg);
        }
    }

    if (csvFiles.size() < 2) {
        std::println(stderr, "Nutzung: {} [Optionen] start.csv ziel.csv", argv[0]);
        return 1;
    }

    std::string inputPath = csvFiles[0];
    std::string targetPath = csvFiles[1];
    std::string targetName = fs::path(targetPath).stem().string();

    auto dinoCloud = loadCSV(inputPath);
    if (dinoCloud.empty()) return 1;

    DatasetStats baseline = calculateStats(dinoCloud);
    FileShape target(targetPath);

    std::string frameDir = "../frames/" + targetName;
    fs::create_directories(frameDir);

    // Parallelisierungs-Setup
    int numChains = omp_get_max_threads();
    std::vector<std::vector<Point>> results(numChains, dinoCloud);
    std::vector<double> energies(numChains);

    std::println("Starte {} parallele Optimierungen auf allen Kernen...", numChains);

    auto start = std::chrono::high_resolution_clock::now();

#pragma omp parallel for
    for (int i = 0; i < numChains; ++i) {
        energies[i] = runOptimization(results[i], target, baseline, frameDir, i, saveTimeline);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::println("BENCHMARK_RESULT|{}|{}|{}", targetName, Config::TOTAL_ITERATIONS, duration);

    // Die Kette mit der geringsten "Energie" (nächste Distanz zur Zielform) gewinnt
    auto minIt = std::min_element(energies.begin(), energies.end());
    int bestIdx = std::distance(energies.begin(), minIt);

    std::println("\nBeste Kette: {} mit Energie {:.2f}", bestIdx, energies[bestIdx]);
    saveCSV(results[bestIdx], "../data/output_" + targetName + "_best.csv");

    return 0;
}