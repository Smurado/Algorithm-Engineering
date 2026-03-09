#include "statistics.h"
#include <cmath>

DatasetStats calculateStats(const std::vector<Point>& points) {
    if (points.empty()) return {};

    size_t n = points.size();
    double sum_x = 0.0, sum_y = 0.0;

    // Pass 1: means
    for (const auto& p : points) {
        sum_x += p.x;
        sum_y += p.y;
    }
    double mx = sum_x / n;
    double my = sum_y / n;

    double var_x = 0.0, var_y = 0.0, cov = 0.0;

    // Pass 2: variance and covariance (two-pass for numerical stability)
    for (const auto& p : points) {
        double dx = p.x - mx;
        double dy = p.y - my;
        var_x += dx * dx;
        var_y += dy * dy;
        cov += dx * dy;
    }

    DatasetStats stats;
    stats.mean_x = mx;
    stats.mean_y = my;
    
    // Sample standard deviation with Bessel correction (n-1)
    stats.std_x = std::sqrt(var_x / (n - 1));
    stats.std_y = std::sqrt(var_y / (n - 1));
    
    // Pearson correlation coefficient
    double denom = std::sqrt(var_x * var_y);
    stats.correlation = (denom > 0) ? (cov / denom) : 0;

    return stats;
}