# Topic

From Lecture 1, take your parallelized version of
pi_monte_carlo.cpp and modify it based on the insights from
Example 3.5 on computing π using random shooting,
particularly the random number generation method. Report
the changes you do and their impact on performance.

# Changes

- Switched out the existing random number generator from the standard library for the one in Example 3.5.
- Used the OpenMP _for_ construct
    - _for_-loop now iterates over n; not just over a fraction of n

- Used the OpenMP _reduction_ construct
    - removed _atomic_ section and unnecessary variables

## Performance

Both versions were executed with 8 threads and Pi is calculated with 100.000.000 points.
The program is executed with the following flags:

> -fopenmp -Ofast

Every version will be executed 5 times, the average is calculated.

### Performance before modifying

| Run 	| Time      |
|-----	|-----------|
| 1   	| 0.238330  |
| 2   	| 0.241048  |
| 3   	| 0.236475  |
| 4   	| 0.240788  |
| 5   	| 0.237752  |

On average the program needs **0.2388786** seconds to execute.

### Performance after modifying

| Run 	| Time      |
|-----	|-----------|
| 1   	| 0.035332 	|
| 2   	| 0.033664 	|
| 3   	| 0.034280 	|
| 4   	| 0.035342 	|
| 5   	| 0.035118  |

On average the program needs **0.0347472** seconds to execute.

### Conclusion

The formula _(old - new) / old * 100_ is used to calculate the percentage improvement in execution time.

After modifying the algorithm, there was a **85.45%** gain in performance.
