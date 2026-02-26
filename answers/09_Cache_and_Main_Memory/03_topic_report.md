# Topic

Select one slide from the lecture, research more about the
topic, and report on it.

## Selected topic

Slide 4 "Processor-Memory Gap"

## Research

A thing i found particularly interesting about processor-memory gap is, that I thought it is a bandwith problem. But in modern System this is not the Case. The main problem of this gap is the latency. While CPUs can have performe billions of operations (4 GHz of a typical CPU = 0,25 nanoseconds per tick). DRAM Latency is somewhere around 100 nanoseconds which means the CPU can do 400 operations while waiting for new data from the memory.

# Optimizations to narrow this gap

1. Increase of the size of Cache
   As discussed in the lesson the cache sized is increased. For Gamers especially AMD released special CPUs with more L3 Cache as games scale very good with larger caches.

2. Optimization of the way data is stored in the memory
   Also mentioned in previuos lessons, the data is stored in better ways to access the data better.
   One example for this is Aos vs Soa.

3. Some manufactures also changes the design of their computers entirly.
   One famous example is the processor `Fujitsu A64FX`. This processor used HBM memory directly attached to the CPU. HBM is interesting because it is stacked memory therefore reduces the distance data has to travel. But it is not designed for high Compute-Bound but rather Bandwith bound. Typcal DDR5 has around 50GB/s of bandwith the HBM is attached in a way to reach 1024 GB/s.