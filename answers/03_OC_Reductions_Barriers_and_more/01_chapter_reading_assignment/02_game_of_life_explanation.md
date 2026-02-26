# Question

What do you think, does the code snippet in Listing 3.10 use
the cores eﬃciently, why yes, why no. Consider also the
variable size in your argumentation.

# Answer

The cores get used efficiently but the efficiency of the program depends heavily on the value of size.
If size is <20 the overhead of creating and scheduling all the threads is not worth it.
If size is >100 the efficiency of the whole program gets significantly better as the overhead gets neglectable.

# Conclusion

The cores get used efficiently. 
The programs efficiency is highly dependent on the value of size.