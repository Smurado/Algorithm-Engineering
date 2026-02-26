#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>

// Basis-Struktur für die Punkte
struct Point {
    double x;
    double y;
};

// Hier ist die gesuchte Struktur:
// Sie speichert die 5 Kennzahlen, die das "Anscombe's Quartett" definieren
struct DatasetStats {
    double mean_x;      // Mittelwert X
    double mean_y;      // Mittelwert Y
    double std_x;       // Standardabweichung X
    double std_y;       // Standardabweichung Y
    double correlation; // Pearson-Korrelationskoeffizient
};

// Prototyp der Rechenfunktion
DatasetStats calculateStats(const std::vector<Point>& points);

#endif