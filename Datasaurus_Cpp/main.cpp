// Datasaurus C++ — Simulated Annealing for statistical shape morphing
//
// Transforms a 2D point cloud into a target shape while preserving
// five summary statistics (mean_x, mean_y, std_x, std_y, correlation).
// Uses O(1) incremental updates and OpenMP multi-chain parallelization.

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

// Reads a CSV file with "x,y" rows into a point vector. Skips malformed lines.
std::vector<Point> loadCSV(const std::string& filename) {
    std::vector<Point> cloud;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::println(stderr, "Error: Could not open file '{}'", filename);
        std::println(stderr, "Current directory: {}", std::filesystem::current_path().string());
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

// Returns true if all five statistics stay within epsilon of the baseline
bool checkStats(const DatasetStats& base, const DatasetStats& current, double epsilon) {

    return std::abs(base.mean_x - current.mean_x) < epsilon &&
           std::abs(base.mean_y - current.mean_y) < epsilon &&
           std::abs(base.std_x - current.std_x) < epsilon &&
           std::abs(base.std_y - current.std_y) < epsilon &&
           std::abs(base.correlation - current.correlation) < epsilon;
}

// Applies a random displacement to a single point; amplitude decreases with temperature
void perturbPoint(std::vector<Point>& points, size_t idx, std::mt19937& gen, double temp) {
    double amplitude = std::max(Config::MIN_AMPLITUDE, temp * Config::AMPLITUDE_FACTOR);
    std::uniform_real_distribution<double> moveDist(-amplitude, amplitude);

    points[idx].x += moveDist(gen);
    points[idx].y += moveDist(gen);
}

// Writes points to CSV with 6 decimal places (needed for sub-epsilon precision).
void saveCSV(const std::vector<Point>& points, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::println(stderr, "Error: Could not create output file '{}'", filename);
        return;
    }

    // High precision required — distance differences during fine-tuning are marginal
    for (const auto& p : points) {
        file << std::fixed << std::setprecision(6) << p.x << "," << p.y << "\n";
    }

    std::println("Result saved to '{}'", filename);
}

// --- Core Simulated Annealing loop for a single chain ---
// Each chain maintains its own running sums (sX, sY, sX2, sY2, sXY) for O(1)
// statistical updates instead of recomputing over all N points every iteration.
// Returns the final energy (sum of distances to target shape).
double runOptimization(std::vector<Point>& points,
                     const TargetShape& target,
                     const DatasetStats& baseline,
                     const std::string& frameDir,
                     int chainID,
                     bool saveTimeline,
                     const RuntimeConfig& config) {

    // Unique seed per thread to avoid identical sequences
    std::mt19937 gen(std::random_device{}() + chainID);
    std::uniform_real_distribution<double> unitDist(0.0, 1.0);
    std::uniform_int_distribution<size_t> indexDist(0, points.size() - 1);

    double temp = config.startTemp;
    const double n = static_cast<double>(points.size());

    // Compute initial running sums — O(N) once at startup
    double sX = 0, sY = 0, sX2 = 0, sY2 = 0, sXY = 0;
    double currentEnergy = 0;
    for (const auto& p : points) {
        sX += p.x; sY += p.y;
        sX2 += p.x * p.x; sY2 += p.y * p.y;
        sXY += p.x * p.y;
        currentEnergy += target.distanceTo(p);
    }

    for (long long i = 0; i < config.totalIterations; ++i) {
        size_t idx = indexDist(gen);
        Point oldP = points[idx];
        double oldDist = target.distanceTo(oldP);

        perturbPoint(points, idx, gen, temp);
        Point newP = points[idx];

        // O(1) incremental statistics update: subtract old point, add new point
        double nextSX = sX - oldP.x + newP.x;
        double nextSY = sY - oldP.y + newP.y;
        double nextSX2 = sX2 - (oldP.x * oldP.x) + (newP.x * newP.x);
        double nextSY2 = sY2 - (oldP.y * oldP.y) + (newP.y * newP.y);
        double nextSXY = sXY - (oldP.x * oldP.y) + (newP.x * newP.y);

        // Derive new statistics from updated sums (Bessel-corrected variance)
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

        // Two-gate acceptance: first check statistical constraint, then Metropolis energy criterion
        if (checkStats(baseline, nextStats, config.epsilon)) {
            double newDist = target.distanceTo(newP);
            double deltaE = newDist - oldDist;

            // Metropolis criterion: accept improvements, occasionally accept worse moves to escape local minima
            if (deltaE < 0 || (temp > 0.000001 && unitDist(gen) < std::exp(-deltaE / temp))) {
                currentEnergy += deltaE;
                sX = nextSX; sY = nextSY; sX2 = nextSX2; sY2 = nextSY2; sXY = nextSXY;
            } else {
                points[idx] = oldP; // Reject: energy too high
            }
        } else {
            points[idx] = oldP; // Reject: statistics violated
        }

        // Logarithmic snapshot schedule: denser early on, sparser later (for smooth GIF animation)
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

        temp *= config.coolingRate;
    }

    if (chainID == 0) {
        saveCSV(points, frameDir + "/frame_final.csv");
    }

    return currentEnergy;
}

void printStats(const std::string& label, const DatasetStats& stats) {
    std::println("  {:>12}  mean_x={:.4f}  mean_y={:.4f}  std_x={:.4f}  std_y={:.4f}  corr={:.4f}",
                 label, stats.mean_x, stats.mean_y, stats.std_x, stats.std_y, stats.correlation);
}

void printHelp(const char* progName) {
    std::println("Usage: {} [OPTIONS] <input.csv> <target.csv>", progName);
    std::println("Options:");
    std::println("  -h, --help          Show this help message");
    std::println("  -t, --timeline      Save intermediate snapshots for animation");
    std::println("  -n, --iterations N  Number of iterations (default: {})", Config::DEFAULT_ITERATIONS);
    std::println("  --temp T            Start temperature for simulated annealing (default: {})", Config::DEFAULT_START_TEMP);
    std::println("  --epsilon E         Statistical tolerance (default: {})", Config::DEFAULT_EPSILON);
    std::println("  -j, --threads J     Number of parallel chains/threads (default: all cores)");
    std::println("  -o, --output FILE   Output path for result (default: ./output_<target>_best.csv)");
    std::println("  -b, --benchmark J   Run benchmark: 5 runs each for 1 to J threads, print summary table");
    std::println("\nExample:");
    std::println("  {} -j 8 -o result.csv --timeline -n 500000000 data/dino.csv data/circle.csv", progName);
    std::println("  {} -b 16 data/dino.csv data/circle.csv", progName);
}

int main(int argc, char* argv[]) {
    std::vector<std::string> csvFiles;
    bool saveTimeline = false;
    int numThreads = 0;
    int benchmarkMaxThreads = 0;
    std::string outputPath;
    RuntimeConfig config;

    // CLI argument parser
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            printHelp(argv[0]);
            return 0;
        }
        else if (arg == "-t" || arg == "--timeline") {
            saveTimeline = true;
        }
        else if ((arg == "-n" || arg == "--iterations") && i + 1 < argc) {
            config.totalIterations = std::stoll(argv[++i]);
        }
        else if (arg == "--temp" && i + 1 < argc) {
            config.startTemp = std::stod(argv[++i]);
        }
        else if (arg == "--epsilon" && i + 1 < argc) {
            config.epsilon = std::stod(argv[++i]);
        }
        else if ((arg == "-j" || arg == "--threads") && i + 1 < argc) {
            numThreads = std::stoi(argv[++i]);
        }
        else if ((arg == "-o" || arg == "--output") && i + 1 < argc) {
            outputPath = argv[++i];
        }
        else if ((arg == "-b" || arg == "--benchmark") && i + 1 < argc) {
            benchmarkMaxThreads = std::stoi(argv[++i]);
        }
        else if (arg.length() >= 4 && arg.substr(arg.length() - 4) == ".csv") {
            csvFiles.push_back(arg);
        }
    }

    // Derive cooling rate from iterations and start temperature
    config.coolingRate = Config::computeCoolingRate(config.totalIterations, config.startTemp);

    if (csvFiles.size() < 2) {
        std::println(stderr, "Usage: {} [OPTIONS] input.csv target.csv", argv[0]);
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

    // --- Benchmark mode: sweep thread counts 1..J, 5 runs each ---
    if (benchmarkMaxThreads > 0) {
        constexpr int RUNS = 5;
        std::println("Benchmark: {} run(s) per thread count, 1 to {} threads, {} iterations each",
                     RUNS, benchmarkMaxThreads, config.totalIterations);
        std::println("");
        printStats("baseline", baseline);
        std::println("");

        struct BenchRow { int threads; double avgTime; double avgEnergy; };
        std::vector<BenchRow> table;

        for (int t = 1; t <= benchmarkMaxThreads; ++t) {
            double totalTime = 0;
            double totalEnergy = 0;

            for (int run = 0; run < RUNS; ++run) {
                omp_set_num_threads(t);
                std::vector<std::vector<Point>> res(t, dinoCloud);
                std::vector<double> eng(t);

                auto t0 = std::chrono::high_resolution_clock::now();
                #pragma omp parallel for
                for (int c = 0; c < t; ++c) {
                    eng[c] = runOptimization(res[c], target, baseline, frameDir, c, false, config);
                }
                auto t1 = std::chrono::high_resolution_clock::now();
                double ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();

                double bestEnergy = *std::min_element(eng.begin(), eng.end());
                totalTime += ms;
                totalEnergy += bestEnergy;

                std::println("  threads={:>2}  run={}/{}  time={:.1f}s  energy={:.2f}",
                             t, run + 1, RUNS, ms / 1000.0, bestEnergy);
            }

            table.push_back({t, totalTime / RUNS, totalEnergy / RUNS});
        }

        std::println("");
        std::println("{:>10} {:>14} {:>14}", "Threads", "Avg Time (s)", "Avg Energy");
        std::println("{}", std::string(40, '-'));
        for (const auto& row : table) {
            std::println("{:>10} {:>14.2f} {:>14.2f}", row.threads, row.avgTime / 1000.0, row.avgEnergy);
        }

        return 0;
    }

    // --- Normal mode: run K independent chains in parallel, keep the best result ---
    int numChains = (numThreads > 0) ? numThreads : omp_get_max_threads();
    omp_set_num_threads(numChains);
    std::vector<std::vector<Point>> results(numChains, dinoCloud);
    std::vector<double> energies(numChains);

    std::println("Starting {} parallel optimization chain(s) on {} thread(s)...", numChains, numChains);
    std::println("");
    std::println("Statistics:");
    printStats("baseline", baseline);
    std::println("");

    auto start = std::chrono::high_resolution_clock::now();

#pragma omp parallel for
    for (int i = 0; i < numChains; ++i) {
        energies[i] = runOptimization(results[i], target, baseline, frameDir, i, saveTimeline, config);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::println("BENCHMARK_RESULT|{}|{}|{}", targetName, config.totalIterations, duration);

    auto minIt = std::min_element(energies.begin(), energies.end());
    int bestIdx = std::distance(energies.begin(), minIt);

    DatasetStats finalStats = calculateStats(results[bestIdx]);

    std::println("\nDone in {:.1f}s — best chain: {} (energy: {:.2f})",
                 duration / 1000.0, bestIdx, energies[bestIdx]);
    std::println("");
    std::println("Statistics comparison:");
    printStats("baseline", baseline);
    printStats("result", finalStats);
    std::println("  {:>12}  mean_x={:.4f}  mean_y={:.4f}  std_x={:.4f}  std_y={:.4f}  corr={:.4f}",
                 "delta",
                 std::abs(baseline.mean_x - finalStats.mean_x),
                 std::abs(baseline.mean_y - finalStats.mean_y),
                 std::abs(baseline.std_x - finalStats.std_x),
                 std::abs(baseline.std_y - finalStats.std_y),
                 std::abs(baseline.correlation - finalStats.correlation));

    if (outputPath.empty()) {
        outputPath = "output_" + targetName + "_best.csv";
    }
    saveCSV(results[bestIdx], outputPath);

    return 0;
}