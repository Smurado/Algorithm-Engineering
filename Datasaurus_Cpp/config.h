#ifndef DATASAURUS_CPP_CONFIG_H
#define DATASAURUS_CPP_CONFIG_H

#include <cmath>

namespace Config {
    // CLI parameter defaults
    inline constexpr int DEFAULT_ITERATIONS = 1'000'000'000;
    inline constexpr double DEFAULT_START_TEMP = 0.4;
    inline constexpr double DEFAULT_EPSILON = 0.003;

    // Internal constants (not exposed via CLI)
    inline constexpr double END_TEMP = 0.00002;
    inline constexpr double AMPLITUDE_FACTOR = 1.0;
    inline constexpr double MIN_AMPLITUDE = 0.01;

    // Computes cooling rate so temperature decays from startTemp to END_TEMP over n iterations
    inline double computeCoolingRate(int iterations, double startTemp) {
        return std::pow(END_TEMP / startTemp, 1.0 / iterations);
    }
}

// Runtime configuration, populated from CLI arguments
struct RuntimeConfig {
    int totalIterations = Config::DEFAULT_ITERATIONS;
    double startTemp = Config::DEFAULT_START_TEMP;
    double epsilon = Config::DEFAULT_EPSILON;
    double coolingRate = Config::computeCoolingRate(Config::DEFAULT_ITERATIONS, Config::DEFAULT_START_TEMP);
};

#endif //DATASAURUS_CPP_CONFIG_H