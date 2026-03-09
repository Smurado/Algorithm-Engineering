# Topic

Read the paper "Analyzing Vectorized Hash Tables Across CPU Architectures".
Discuss two things you find particularly interesting.

## Topic 1

### Scalar Hashing Schemes

The scalar hashing scheme is the basic version of hashing. 
It uses standard CPU instructions and hashes one element at a time, making it strictly serial.

It is used in simple hash functions and gets applied in scenarios where the data can be easily processed one-by-one.
It is very simple, but the performance gets worse at high load factors (when the table is full).
The paper states that it can be faster than vectorized hashing when it's nearly empty.

Some examples of applications that use scalar hashing schemes: 

1. Standard Data Structures (HashTable, HashMap)
2. Checksums (Validation of downloaded ISO images)
3. Small databases

## Topic 2

### Vectorized Hashing Schemes

Vectorized hashing is a more advanced hashing scheme. 
It can process multiple elements of data simultaneously as a hardware vector.
Because of this, it's often used when throughput is crucial and when working with high load factors (memory constraints).
It heavily exploits SIMD instructions (like AVX, NEON, SVE), as learned in the last lessons.

Examples where vectorized hashing schemes are used:

1. Graphics Processing (Rendering and image processing)
2. Network Security (Analysis of network traffic)
3. In-Memory Databases (Optimized for modern hardware)