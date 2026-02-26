import matplotlib.pyplot as plt
from matplotlib.lines import Line2D
import pandas as pd

def plot_threads_benchmark_custom():
    # 1. Daten laden (Die Datei mit den Thread-Daten)
    filename = 'speedup_benchmark.csv'

    try:
        df = pd.read_csv(filename)
    except FileNotFoundError:
        print(f"FEHLER: Datei '{filename}' nicht gefunden.")
        return

    # 2. Plot erstellen
    fig, ax = plt.subplots(figsize=(10, 6))

    col_min_max = '#1f77b4' # Blau
    col_gnu = 'orange'      # Orange
    col_ideal = 'gray'      # Grau für die Ideallinie

    # --- Die Linien zeichnen ---
    # Min Max Quicksort
    ax.plot(df['threads'], df['speedup_min_max'],
            marker='o', linestyle='-', linewidth=2, color=col_min_max)

    # GNU Parallel
    ax.plot(df['threads'], df['speedup_gnu'],
            marker='s', linestyle='-', linewidth=2, color=col_gnu)

    # Ideale Skalierung (Diagonal)
    ax.plot(df['threads'], df['threads'],
            linestyle='--', linewidth=1.5, alpha=0.6, color=col_ideal)

    # --- CUSTOM LEGENDE (Line2D Objekte) ---
    legend_elements = [
        Line2D([0], [0], color=col_min_max, lw=2, marker='o', markersize=8, label='min_max_quicksort'),
        Line2D([0], [0], color=col_gnu,     lw=2, marker='s', markersize=8, label='__gnu_parallel::sort'),
        Line2D([0], [0], color=col_ideal,   lw=2, linestyle='--',           label='Ideal Linear Speedup')
    ]

    # Legende hinzufügen
    ax.legend(handles=legend_elements, loc='upper left', fontsize=11, frameon=True)

    # Beschriftungen
    ax.set_xlabel('Number of Threads', fontsize=12)
    ax.set_ylabel('Relative Speedup over std::sort', fontsize=12)
    ax.set_title('Parallel Speedup Analysis (Array Size: $10^9$)', fontsize=14)

    # Grid und Ticks
    ax.grid(True, linestyle='--', alpha=0.6)
    ax.set_xticks(df['threads']) # Zeigt alle Threads (1, 2, ..., 16) an

    plt.tight_layout()
    plt.savefig('speedup_graph_custom.png', dpi=300)
    print("Graph gespeichert als 'speedup_graph_custom.png'")
    plt.show()

if __name__ == "__main__":
    plot_threads_benchmark_custom()