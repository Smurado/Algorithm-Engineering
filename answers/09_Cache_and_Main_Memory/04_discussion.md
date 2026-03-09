# Topic

Read the paper "An Overview of Cache Optimization Techniques and Cache-Aware Numerical Algorithms".
Discuss two things you find particularly interesting.

## Topic 1

Cache data replacement

## Discussion 1

In chapter 10.2.3, the author talks about cache data replacement policies/strategies. They determine which memory block gets replaced when something new needs to be stored in the cache.

There seem to be 4 methods mentioned in the paper:

- **Random**
  As the name suggests, the block in the cache that gets overwritten is picked randomly. This method is very easy to implement and has very minimal administrative overhead, but it can accidentally delete important data that is still needed.

- **LRU (Least Recently Used)**  
  As the name suggests, it overwrites the block that was used least recently. Based on temporal locality, things that were used recently have a higher chance of being needed again than things that were loaded a long time ago. It is highly efficient, but it does require keeping track of access times for the data.

- **LFU (Least Frequently Used)**
  As the name suggests, it overwrites the block that was used the least frequently. Each block gets a counter which gets increased with each use. In return, often-used data will not be replaced. A downside is that old data that was used heavily in the past might not get overwritten, even if it is no longer needed.
  
- **FIFO (First-In, First-Out)**
  As the name suggests, the block that was loaded first will get deleted first. It doesn't matter if the data is still being used. The implementation is simple, but the hit rate is typically not as good as LRU.

## Topic 2

Loop Interchange

## Discussion 2

In chapter 10.3.1, the author talks about data access optimizations, especially _loop interchange_. As I didn't fully understand it the first time, I read some more sources about it and found it to be absolutely logical, yet it's something we don't naturally think about when programming.

**Loop interchange**, as the name suggests, "switches" the order of nested loops with the goal of achieving better cache utilization (and optionally vectorization and parallelism). An example is:

```c++
// Original (Column-major access in C++)
double sum;
double a[n, n];
for j = 1 to n do
  for i = 1 to n do
    sum += a[i, j];
  end for
end for

// Modified
double sum;
double a[n, n];
for i = 1 to n do
  for j = 1 to n do
    sum += a[i, j];
  end for
end for
```

This works because it uses the cache line much better due to spatial locality.

By switching the loops, the code reads data sequentially in memory order (row-major order in C/C++). When the processor loads a cache line from main memory for the first number, the next few numbers are already inside that same cache line. This means the program uses all the data in the cache line immediately, instead of constantly fetching new lines from slow memory and only working with a single item from each line (cache thrashing).