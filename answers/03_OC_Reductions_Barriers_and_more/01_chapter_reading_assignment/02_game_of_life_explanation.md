# Question

What do you think, does the code snippet in Listing 3.10 use
the cores eﬃciently, why yes, why no. Consider also the
variable size in your argumentation.

# Answer

The cores are used efficiently, but the overall efficiency of the program depends on several factors:

1. The code snippet for computing generations of Conway's "Game of Life" contains two nested _for_-loops. To parallelize them effectively, the _for collapse(...)_ directive of OpenMP is used in Line 2, which allows the compiler to collapse both loops into one and distribute the iterations across threads.

2. The algorithm works with two separate planes. One plane holds the current generation and is only read from, while the other plane stores the next generation and is only written to. This separation of read and write access avoids race conditions between threads.

3. The variable _size_ defines the height and width of the matrix. Depending on how large or small the number stored in this variable is, there can be a huge amount of computation necessary. In the chapter, _size_ is set to 10, so there are 100 cells in the matrix. But if _size_ is e.g. set to 100, there are 10.000 cells. This in itself is not a problem, but when using just e.g. 10 threads and those 10.000 iterations get executed repetitively by the _while_-loop, the cores won't get used efficiently. For small values of `size`, the overhead of creating and scheduling threads outweighs the benefits of parallelization. For larger values, the threading overhead becomes negligible compared to the computation time, and the cores are used more efficiently.

# Conclusion

The cores are used efficiently for sufficiently large values of `size`, as the parallelization strategy (collapse, separate read/write planes) is sound. However, for small values of `size`, the threading overhead dominates and the cores are not used efficiently.