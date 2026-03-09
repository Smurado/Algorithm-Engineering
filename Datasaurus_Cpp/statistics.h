#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>

struct Point {
    double x;
    double y;
};

// The five summary statistics that define Anscombe's Quartet
struct DatasetStats {
    double mean_x;
    double mean_y;
    double std_x;
    double std_y;
    double correlation;
};

DatasetStats calculateStats(const std::vector<Point>& points);

#endif