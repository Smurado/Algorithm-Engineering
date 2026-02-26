# Topic

Slide 4 SSD cell-types

## Difference between SLC, MLC, TLC and QLC in Terms of speed.

Like the name suggests, SLC can store one bit in each cell, while the MLC (2), TLC (3) and QLC (4) can store multiple bits in each cell.
One upcoming Technology is PLC which for now shoud only be used for archiving data because of its low endurance.
To have a better understanding of each cell I will list the main features in a table:

### SSD NAND Flash Comparison (2026)

| NAND Type | Bits per Cell | Voltage Levels | Speed (Latency) | Endurance (P/E Cycles) |
| :--- | :---: | :---: | :--- | :--- |
| **SLC** | 1 | 2 | **Extremely Fast** (~25 µs) | ~100,000 (Ultra-Durable) |
| **MLC** | 2 | 4 | **Very Fast** (~50 µs) | ~10,000 (Pro Workstation) |
| **TLC** | 3 | 8 | **Moderate** (~100 µs) | ~3,000 (Mainstream Standard) |
| **QLC** | 4 | 16 | **Slow** (~200+ µs) | ~1,000 (Budget Storage) |
| **PLC** | 5 | 32 | **Extremely Slow** | < 500 (Archival Use Only) |

Voltage levels corospond with the bits able to write in a cell. For one bit you need two voltage levels for two bits one needs 4 voltage levels to distiguise the two bits state (0,1).

### One addition to MLC, TLC, QLC and PLC

Modern SSDs are optimized for the fact that they are most likely not SLC SSDs. But they can be treated as one. If the SSD gets lots of data, it will only write a Single bit per Cell. This is much faster because the SSD controller doesn't have to rearrange the bits. When the SSD has a low workload, it will rewrite those single bits into the denser cells.
This works best if the SSD is nearly or completly empty.

