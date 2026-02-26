#ifndef DATASAURUS_CPP_CONFIG_H
#define DATASAURUS_CPP_CONFIG_H

namespace Config {
    // Simulations-Steuerung
    // 1 Milliarde Schritte für eine gute Balance aus Speed und Präzision
    inline constexpr int TOTAL_ITERATIONS = 1'000'000'000;
    inline constexpr int SNAPSHOT_INTERVAL = 100'000;

    // Simulated Annealing Parameter
    inline constexpr double START_TEMP = 0.4;
    // Bewusst extrem nah an 1.0 gewählt für eine sehr langsame Auskühlungsphase.
    inline constexpr double COOLING_RATE = 0.99999999;

    // Bewegungsparameter (Perturbation)
    inline constexpr double AMPLITUDE_FACTOR = 1.0;
    inline constexpr double MIN_AMPLITUDE = 0.01;

    // Statistische Toleranz (Epsilon)
    // Wie stark darf die neue Cloud von der Baseline abweichen?
    inline constexpr double EPSILON = 0.003;
}

#endif //DATASAURUS_CPP_CONFIG_H