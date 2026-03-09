# Topic

Select one slide from the lecture, research more about the
topic, and report on it.

## Selected topic

Slide 4 "Processor-Memory Gap"

## Research

A thing I found particularly interesting about the processor-memory gap is that I always thought it is mainly a bandwidth problem. But in modern systems, this is not the case. The main problem of this gap is latency. While CPUs can perform billions of operations per second (e.g., 4 GHz of a typical CPU = 0.25 nanoseconds per clock tick), DRAM latency is somewhere around 100 nanoseconds. This means the CPU could theoretically compute 400 operations while waiting for new data from the main memory.

# Optimizations to narrow this gap

1. **Increase the cache size**
   As discussed in the lecture, cache sizes are continuously increasing. For gamers especially, AMD released special "X3D" CPUs with significantly more L3 Cache, as games scale very well with larger low-latency caches.

2. **Optimization of the memory layout**
   As mentioned in previous lessons, data can be stored in more efficient ways to improve memory access and exploit spatial locality. 
   One example for this is comparing Array of Structures (AoS) vs Structure of Arrays (SoA).

3. **Complete architecture redesigns**
   Some manufacturers completely changed the design of their computers.
   One famous example is the supercomputer processor `Fujitsu A64FX`. This processor uses HBM (High Bandwidth Memory) directly attached to the CPU. HBM is interesting because it is vertically stacked memory, therefore reducing the physical distance data has to travel. It is specifically designed not just to lower latency, but mostly to combat bandwidth-bound scenarios. Typical DDR5 has around 50 GB/s of bandwidth, whereas the HBM layout used on the A64FX reaches an impressive 1024 GB/s.