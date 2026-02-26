#pragma once

#include "statistics.h"
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

// Interface für austauschbare Zielformen (Polymorphismus).
// Erlaubt später einfache Erweiterungen um z.B. mathematisch
// definierte Formen (Kreise, Polygone) ohne Code-Duplizierung.
class TargetShape {
public:
    virtual ~TargetShape() = default;
    virtual double distanceTo(const Point& p) const = 0;
};


class FileShape : public TargetShape {
    std::vector<Point> targetPoints;
    // Lookup-Table (LUT) für vorberechnete Distanzen.
    // Klassischer Space-Time-Tradeoff: Wir opfern ~80 KB RAM,
    // um Milliarden O(N)-Distanzberechnungen waehrend der MCMC-Simulation zu sparen.
    double grid[101][101];

public:
    // 'explicit' verhindert versehentliche implizite Casts von std::string zu FileShape
    explicit FileShape(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string x_str, y_str;
            if (std::getline(ss, x_str, ',') && std::getline(ss, y_str, ',')) {
                try { targetPoints.push_back({std::stod(x_str), std::stod(y_str)}); }
                catch (...) {
                    continue;
                }
            }
        }

        // 2. Grid vorberechnen (Lookup-Table)
        for (int x = 0; x <= 100; ++x) {
            for (int y = 0; y <= 100; ++y) {
                double minDist = 1e9;
                for (const auto& tp : targetPoints) {
                    double d = std::sqrt(std::pow(x - tp.x, 2) + std::pow(y - tp.y, 2));
                    if (d < minDist) minDist = d;
                }
                grid[x][y] = minDist;
            }
        }
    }

    double distanceTo(const Point& p) const override {
        // PERFORMANCE-CORE: Reduktion der Komplexitaet auf O(1) Array-Zugriff.
        // std::clamp garantiert Speichersicherheit (verhindert Segfaults/Out-of-Bounds),
        // falls die Perturbation Punkte temporaer ueber das 100x100 Grid hinausbewegt.
        int ix = std::clamp(static_cast<int>(std::round(p.x)), 0, 100);
        int iy = std::clamp(static_cast<int>(std::round(p.y)), 0, 100);

        return grid[ix][iy];
    }
};
