# Topic

Read the paper "Analyzing Vectorized Hash Tables Across CPU Architectures".
Discuss two things you find particularly interesting.

## Topic 1

### Scalar Hashing Schemes

Scalar Hashing Schemese is the basic version of hashing. 
It uses one CPU and hashes one element at the time therby it's serial.

It is used in simple hash functions and gets applied in scenarios where the data can be easily processed one-by-one.
It is very simple but the performance gets worse at high load factors (when the table is full).
The paper states that it can be faster then vectorized hashing when it's nearly empty.

Some examples for things that use Scalar Hashing Schemes are: 

1. Datastructures (HashTable, HashMap)
2. Checksums (validate downloaded ISO-images)
3. small databases

## Topic 2

### Vectorized Hashing Schemes

Vectorized Hashing Schemes is a more advanced hashing scheme. 
It can process multiple elements of data simultaneously as a vector.
Because of this, it's often used when throughput is crucial and when working with high load factors (memory constraints).
It heavily exploits the SIMD instructions (like AVX, NEON, SVE), as learned in the last lessons.

Expamples for where Vectorized Hashing Schemes are used:

1. Graphics Processing (rendering and image processing)
2. Network Security (analysis of network traffic)
3. In-Memory Databases (optimized for modern hardware)