### This File is for ideas Only!

Wir nehmen C++ Version 23 weil es und syntax-Vorteile bring! (etwas besser ausformulieren!)

Die Logik: Simulated Annealing in 30 Sekunden
Stell dir vor, du hast eine Box mit Sand (deine Punkte). Du willst, dass der Sand die Form einer Stern-Form annimmt.

Verschieben: Du nimmst einen Punkt und schubst ihn ein winziges Stück in eine zufällige Richtung.

Check:

Haben sich die Statistik-Werte (Mittelwert, Korrelation etc.) verändert? Wenn ja: Abgelehnt! Punkt zurück auf Start.

Ist der Punkt jetzt näher an der Zielform? Wenn ja: Gekauft!

Der Clou (Temperatur): Manchmal akzeptieren wir einen Schritt, auch wenn er die Form verschlechtert. Das verhindert, dass der Algorithmus in einer Sackgasse stecken bleibt. Am Anfang (hohe Temperatur) erlauben wir viele schlechte Schritte, am Ende (kalte Temperatur) fast keine mehr.

Da wir „vorarbeiten“ wollen, implementieren wir jetzt das Herzstück von Tag 2: Den eigentlichen Simulated Annealing Loop.Die Logik: Der Metropolis-AlgorithmusUm die Punkte in die neue Form zu zwingen, nutzen wir das physikalische Prinzip des Abkühlens. Die Kernentscheidung im Loop basiert auf dieser Formel für die Akzeptanzwahrscheinlichkeit $P$:$$P = \exp\left(-\frac{\Delta E}{T}\right)$$

$\Delta E$ (Energie-Differenz): Ist die neue Form besser (niedrigere Energie), ist $\Delta E$ negativ und wir akzeptieren den Schritt immer.

$T$ (Temperatur): Am Anfang ist $T$ hoch, wir akzeptieren auch schlechtere Schritte (um lokale Minima zu verlassen). Am Ende ist $T$ fast Null, wir akzeptieren nur noch Verbesserungen.



void runOptimization(std::vector<Point>& points, const TargetShape& target, const DatasetStats& baseline) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> unitDist(0.0, 1.0);

    // Parameter laut Paper/Video
    const int iterations = 200'000;
    double temp = 0.4;
    const double cooling_rate = 0.99995; // Sehr langsames Abkühlen

    double currentEnergy = 0;
    for (const auto& p : points) currentEnergy += target.distanceTo(p);

    std::println("Starte Optimierung: Initial-Energie = {:.2f}", currentEnergy);

    for (int i = 0; i < iterations; ++i) {
        // 1. Punkt sichern und verschieben
        std::uniform_int_distribution<size_t> indexDist(0, points.size() - 1);
        size_t idx = indexDist(gen); // Wir bestimmen den Index HIER
        Point oldPoint = points[idx];

        perturbPoint(points, idx, gen); // Die Funktion zum "Schubsen"

        // 2. Wächter-Check: Statistik noch im Rahmen?
        DatasetStats currentStats = calculateStats(points);
        if (checkStats(baseline, currentStats)) {

            // 3. Energie-Check (Form-Verbesserung)
            double newEnergy = 0;
            // Hier nutzen wir später OpenMP für Performance!
            for (const auto& p : points) newEnergy += target.distanceTo(p);

            double deltaE = newEnergy - currentEnergy;

            // Metropolis-Kriterium
            if (deltaE < 0 || unitDist(gen) < std::exp(-deltaE / temp)) {
                currentEnergy = newEnergy; // Schritt akzeptiert
            } else {
                points[idx] = oldPoint; // Zu schlecht, zurückrollen
            }
        } else {
            points[idx] = oldPoint; // Statistik verletzt, zurückrollen
        }

        // 4. Abkühlen
        temp *= cooling_rate;

        // Logging alle 20.000 Schritte
        if (i % 20000 == 0) {
            std::println("Iteration {:7}: Energie = {:.2f}, Temp = {:.5f}", i, currentEnergy, temp);
        }
    }
    std::println("Optimierung abgeschlossen. Final-Energie = {:.2f}", currentEnergy);
}
