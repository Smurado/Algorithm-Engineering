# Question

What do you think, does the code snippet in Listing 3.10 use
the cores eﬃciently, why yes, why no. Consider also the
variable size in your argumentation.

# Answer

The cores are used efficiently, but the overall efficiency of the program depends heavily on the value of `size`.
If `size` is smaller than 20, the overhead of creating and scheduling the threads outweighs the benefits of parallelization.
If `size` is greater than 100, the efficiency of the program improves significantly because the threading overhead becomes negligible compared to the computation time.

# Conclusion

The cores are used efficiently. 
The program's efficiency is highly dependent on the value of `size`.