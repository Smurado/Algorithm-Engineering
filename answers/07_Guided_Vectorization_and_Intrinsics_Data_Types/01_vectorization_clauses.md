# Topic

Explain three vectorization clauses of your choice that can
be used with `#pragma omp simd`.

# private

**private** ensures that each **SIMD** lane has its own local copy of the variable.

**Example:**
```cpp
void process_data(float* input, float* output, int n, float factor) {
    float temp; 

    #pragma omp simd private(temp)
    for (int i = 0; i < n; i++) {
        temp = input[i] * factor;  
        output[i] = temp + 10.0f;  
    }
}
```

# safelen

**safelen** sets a vector width limit. 
This means, in the example below, that the loop can be vectorized safely with a vector length of 4 or less.

**Example:**
```cpp
void process_data(float* A, int n) {
    #pragma omp simd safelen(4)
    for (int i = 4; i < n; i++) {
        A[i] = A[i-4] * 1.5f;
    }
}
```

# collapse

**collapse** fuses nested loops together and executes them as one.
It has similarities to the loop construct from previous lectures:

> `#pragma omp parallel for collapse(2)`

In this case, it does the same thing (fusing loops together), with the exception that it is an optimization in the context of **SIMD**, which provides the compiler with a larger iteration space to optimize the vectorization if possible.

**Example:**
```cpp
void fill_matrix(float matrix[4][4]) {
    #pragma omp simd collapse(2)
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = 0.0f;
        }
    }
}
```