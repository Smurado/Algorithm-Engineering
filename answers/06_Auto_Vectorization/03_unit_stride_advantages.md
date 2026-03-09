# Topic 

What are the advantages of unit stride (stride-1) memory
access compared to accessing memory with larger strides (for
example, stride-8)?

## Answer

**Stride** refers to the step size when accessing elements in memory.
If one accesses every 2nd element in an array, it is called **stride-2** memory access.

**Stride-1** (unit stride) means that the data is accessed sequentially, one element after another, exactly as it is laid out in contiguous memory.
The great advantage is that all the data needed for a vector operation can be loaded into a register in a single fast operation (contiguous load). Larger strides require specific gather commands or multiple scalar loads to fetch non-contiguous elements, which is very inefficient and heavily limits the performance benefits of SIMD instructions.
