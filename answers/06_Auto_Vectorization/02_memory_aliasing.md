# Topic 
How can memory aliasing affect performance?

## Answer

Compilers are pessimistic. 
If a function has multiple pointers the compiler assumes that those points point to the same memory address.
Therefor the compiler wont optimize the code to it's fullest potential.
The programmer can guarantee this, by addin gthe keyword `__restrict__` to the pointer.

**example:**<br>
function without restriction:
```c++
void important_function(
    int* in, 
    int* out
);
```
function with restriction:
```c++
void important_function(
    int*__restrict__ in, 
    int*__restrict__ out
);
```

The second example enables the compiler to make drastic improvements.