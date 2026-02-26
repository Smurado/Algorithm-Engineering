# Topic 
What are the advantages of unit stride (stride-1) memory
access compared to accessing memory with larger strides (for
example, stride-8)?

## Answer

**Stride** Stride Access defines the access of elements within the same distance.
If one accesses every 2nd element in an array, its called **stride 2** memory access.


**Stride 1** means, that the data used from the memory is written one after another. 
So all the data needed for a vector operation can be accessed/loaded in a single operation rather than using
specified command to access them as those commands are very inefficient.