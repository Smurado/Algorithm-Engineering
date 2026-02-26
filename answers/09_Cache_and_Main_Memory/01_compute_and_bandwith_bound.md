# Topic

How do bandwidth-bound computations differ from
compute-bound computations?

# Answer

**Compute-bound computations** are tasks where the performance is limited by the speed of the processor. The processor is used heavily and performs calculations 100% of the time, while the memory can easily deliver data faster than the processor can consume it. (e.g. calculation pi via numerical integration).

**Bandwidth-bound computations** are tasks where the performance is limited by the speed of the main memory. The processor sends a significant amount of time wiating for data to be transferred from memory. So the CPU could theoretically precess data faster but the transfere between cpu and memory is not fast enough.

In summary: The main diffrence is the bottleneck:
    - **Compute-bound computations:** CPU is the bottleneck
    - **Bandwidth-bound computations:** data transfer speed between memory and CPU is the bottleneck
