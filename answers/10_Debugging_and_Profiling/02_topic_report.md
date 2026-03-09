# Topic

Select one slide from the lecture, research more about the
topic, and report on it.

## Selected topic

Page 11, Intel Vtune Amplifier

I wanted to find out something about the history of this kind of tool with Intel, as Intel is known to abandon such tools relatively quickly.

### History

- **Visual Tune (90s):**
    One of the first iterations of this tool, it implemented one of the first graphical ways to analyze functions for pipeline optimization.

- **Intel VTune Performance Analyzer (2000):**
    VTune used the CPU's built-in hardware (PMU) to take quick snapshots of what the processor was actually doing. This allowed developers to find the code's 'hotspots'.

- **Intel VTune Amplifier (2010):**
    VTune Amplifier shifted its focus to the multicore revolution by introducing thread analysis specifically for 'locks and waits' to better search for inefficiently parallelized software.

- **Intel VTune Profiler (2020):**
    Transformed the tool into a cross-architecture tool under oneAPI, which in return meant that it could be used for performance optimization on CPUs, GPUs, and FPGAs.