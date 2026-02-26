import matplotlib.pyplot as plt
from matplotlib.lines import Line2D
import pandas as pd

def plot_size_benchmark_clean_grid():
    # 1. Daten laden
    filename = 'size_benchmark.csv'

    try:
        df = pd.read_csv(filename)
    except FileNotFoundError:
        print(f"FEHLER: Datei '{filename}' nicht gefunden.")
        return

    # 2. Plot erstellen
    fig, ax = plt.subplots(figsize=(10, 6))

    col_min_max = '#1f77b4' # Blau
    col_gnu = 'orange'      # Orange

    # --- Linien zeichnen ---
    ax.plot(df['size'], df['speedup_min_max'],
            marker='o', linestyle='-', linewidth=2, color=col_min_max)

    ax.plot(df['size'], df['speedup_gnu'],
            marker='s', linestyle='-', linewidth=2, color=col_gnu)

    # Referenzlinie
    ax.axhline(y=1.0, color='gray', linestyle='--', alpha=0.5)

    # --- Achsen ---
    ax.set_xscale('log')

    # --- FIX FÜR DEN HINTERGRUND ---
    # Nur 'major' Grid-Lines an den Exponenten (10, 100, 1000...)
    ax.grid(True, which='major', linestyle='--', linewidth=0.75, color='gray', alpha=0.6)

    # Optional: Wenn du das vertikale Gitter ganz weg haben willst und nur horizontale Linien:
    # ax.grid(True, axis='y', linestyle='--', alpha=0.6)

    # --- Legende ---
    legend_elements = [
        Line2D([0], [0], color='gray',      lw=2, linestyle='--',           label='Baseline (std::sort)'),
        Line2D([0], [0], color=col_gnu,     lw=2, marker='s', markersize=8, label='__gnu_parallel::sort'),
        Line2D([0], [0], color=col_min_max, lw=2, marker='o', markersize=8, label='min_max_quicksort'),
    ]
    ax.legend(handles=legend_elements, loc='upper left', fontsize=11, frameon=True)

    # Labels
    ax.set_xlabel('Array Size (Log Scale)', fontsize=12)
    ax.set_ylabel('Relative Speedup over std::sort', fontsize=12)
    ax.set_title('Speedup vs. Array Size (16 Threads)', fontsize=14)

    plt.tight_layout()
    plt.savefig('size_benchmark_graph.png', dpi=300)
    print("Graph gespeichert als 'size_benchmark_graph.png'")
    plt.show()

if __name__ == "__main__":
    plot_size_benchmark_clean_grid()