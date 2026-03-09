#pragma once

#include "statistics.h"
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

// Abstract base class for target shapes (allows file-based and parametric shapes)
class TargetShape {
public:
    virtual ~TargetShape() = default;
    virtual double distanceTo(const Point& p) const = 0;
};


class FileShape : public TargetShape {
    std::vector<Point> targetPoints;
    // Precomputed distance lookup table (LUT): trades ~80 KB RAM for O(1) distance queries
    double grid[101][101];

public:
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

        // Precompute distance grid
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
        // O(1) grid lookup; out-of-bounds points get an additional penalty
        // proportional to their distance from the grid, creating a gradient back inward
        int ix = std::clamp(static_cast<int>(std::round(p.x)), 0, 100);
        int iy = std::clamp(static_cast<int>(std::round(p.y)), 0, 100);

        double baseDist = grid[ix][iy];

        double dx = std::max({0.0, -p.x, p.x - 100.0});
        double dy = std::max({0.0, -p.y, p.y - 100.0});
        double penalty = std::sqrt(dx * dx + dy * dy);

        return baseDist + penalty;
    }
};
