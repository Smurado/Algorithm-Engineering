# Topic

How do bandwidth-bound computations differ from
compute-bound computations?

# Answer

**Compute-bound computations** are tasks where the performance is limited by the speed of the processor. The processor is used heavily and performs calculations 100% of the time, while the memory can easily deliver data faster than the processor can consume it. (e.g. calculating Pi via numerical integration).

**Bandwidth-bound computations** are tasks where the performance is limited by the speed of the main memory. The processor spends a significant amount of time waiting for data to be transferred from memory. The CPU could theoretically process data much faster, but the transfer speed between CPU and memory is just not fast enough.

In summary, the main difference is the bottleneck:
- **Compute-bound computations:** The CPU is the bottleneck.
- **Bandwidth-bound computations:** The data transfer speed between memory and the CPU is the bottleneck.
