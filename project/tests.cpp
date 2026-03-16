#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <vector>
#include "statistics.h"
#include "config.h"

TEST_CASE("Mean is calculated correctly", "[statistics]") {
    std::vector<Point> data = {{0, 0}, {10, 10}, {5, 5}};

    DatasetStats stats = calculateStats(data);

    // WithinAbs replaces a manual isClose check
    REQUIRE_THAT(stats.mean_x, Catch::Matchers::WithinAbs(5.0, 0.001));
    REQUIRE_THAT(stats.mean_y, Catch::Matchers::WithinAbs(5.0, 0.001));
}

TEST_CASE("Correlation of a perfect diagonal is 1.0", "[statistics]") {
    std::vector<Point> data = {{1, 1}, {2, 2}, {3, 3}};

    DatasetStats stats = calculateStats(data);

    REQUIRE_THAT(stats.correlation, Catch::Matchers::WithinAbs(1.0, 0.001));
}

// ==========================================
// Config & Parameter Tests
// ==========================================

TEST_CASE("RuntimeConfig has correct defaults", "[config]") {
    RuntimeConfig config;

    REQUIRE(config.totalIterations == 1'000'000'000);
    REQUIRE_THAT(config.startTemp, Catch::Matchers::WithinAbs(0.4, 1e-9));
    REQUIRE_THAT(config.epsilon, Catch::Matchers::WithinAbs(0.003, 1e-9));
    REQUIRE(config.coolingRate > 0.0);
    REQUIRE(config.coolingRate < 1.0);
}

TEST_CASE("computeCoolingRate produces valid values", "[config]") {
    // Default rate must be very close to 1.0 (slow cooling)
    double rate = Config::computeCoolingRate(1'000'000'000, 0.4);
    REQUIRE(rate > 0.999999);
    REQUIRE(rate < 1.0);

    // Fewer iterations -> more aggressive cooling (smaller rate)
    double fastRate = Config::computeCoolingRate(1'000'000, 0.4);
    REQUIRE(fastRate < rate);
    REQUIRE(fastRate > 0.0);
    REQUIRE(fastRate < 1.0);
}

TEST_CASE("computeCoolingRate: temperature reaches END_TEMP after N iterations", "[config]") {
    int iterations = 1'000'000;
    double startTemp = 0.4;
    double rate = Config::computeCoolingRate(iterations, startTemp);

    double temp = startTemp;
    for (int i = 0; i < iterations; ++i) {
        temp *= rate;
    }

    REQUIRE_THAT(temp, Catch::Matchers::WithinAbs(Config::END_TEMP, 1e-6));
}

TEST_CASE("computeCoolingRate scales correctly with start temperature", "[config]") {
    // Higher start temperature -> steeper decay needed -> smaller rate
    double rateHigh = Config::computeCoolingRate(1'000'000, 1.0);
    double rateLow  = Config::computeCoolingRate(1'000'000, 0.1);

    REQUIRE(rateHigh < rateLow);
}