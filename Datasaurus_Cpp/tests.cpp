#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <vector>
#include "statistics.h"

TEST_CASE("Mittelwert wird korrekt berechnet", "[statistics]") {
    // Simple Testdaten: (0+10+5)/3 = 5
    std::vector<Point> data = {{0, 0}, {10, 10}, {5, 5}};

    DatasetStats stats = calculateStats(data);

    // WithinAbs ersetzt den manuellen isClose-Check
    REQUIRE_THAT(stats.mean_x, Catch::Matchers::WithinAbs(5.0, 0.001));
    REQUIRE_THAT(stats.mean_y, Catch::Matchers::WithinAbs(5.0, 0.001));
}

TEST_CASE("Lineare Korrelation einer geraden Linie ist 1.0", "[statistics]") {
    // Perfekte Diagonale y = x -> r muss genau 1.0 sein
    std::vector<Point> data = {{1, 1}, {2, 2}, {3, 3}};

    DatasetStats stats = calculateStats(data);

    REQUIRE_THAT(stats.correlation, Catch::Matchers::WithinAbs(1.0, 0.001));
}