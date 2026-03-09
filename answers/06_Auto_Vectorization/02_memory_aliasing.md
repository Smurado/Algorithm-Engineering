# Topic 
How can memory aliasing affect performance?

## Answer

Compilers are pessimistic. 
If a function receives multiple pointers, the compiler assumes that these pointers might point to the same memory address (memory aliasing).
Therefore, the compiler won't optimize the code to its fullest potential to avoid causing bugs when modifying shared data.
The programmer can guarantee that pointers do not overlap by adding the keyword `__restrict__` to the pointers.

**example:**<br>
Function without restriction:
```c++
void important_function(
    int* in, 
    int* out
);
```
Function with restriction:
```c++
void important_function(
    int* __restrict__ in, 
    int* __restrict__ out
);
```

The second example enables the compiler to make drastic performance improvements.