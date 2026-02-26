# Topic

Read the paper "An Overview of Cache Optimization
Techniques and Cache-Aware Numerical Algorithms".Discuss two things you find particularly interesting.

## Topic 1

cache data replacement

## Discussion 1

In chapter 10.2.3, the author talks about cache data replacement policies/strategies. They determine which memory block gets replaced when something new needs to be stored in memory.

There seem to be 3 methods mentiond in the paper are the following:

- Random
  As the name suggest here the block in the cache that gets overwritten is picked randomly. This method is very easy to implement and has very minimal administrative expenses but it can delete important data by accident/design.


- LRU (Least Recently Used)  
  As the name suggest it overwrites the block that was used least recently. Things that are used recently will be needed again with a higher chance than things that are loaded since long ago. It is highly efficient but it does require to kep track of time of the data.

- LFU (Least Frequently Used)
  As the name suggest it overwerites the block that was used the least frequently. Each block gets a counter which gets increased with each use. In return often used data will not be replaced. A downside is that old data that was used heavily in the past will likely not get overwritten.
  

- FIFO (First-in First-Out)
  As the name suggest the block that was loaded first will get deleted first. It hearby doesnt matter if data is still used. The implementation is simple but the hit-rata is not as good.

## Topic 2

Loop interchange

## Discussion 2

In chapter 10.3.1, the author talks about data access optimizations, especially _loop interchange_. As I didn't understand it the first time I read some more sources about it an thought it to be absolutly logical but something we dont think about naturally when programming.

**Loop interchange** as the name suggests, "switches" the order of the loops with the goal of better vectorization and parallelism. An example is:

```c++
// Original
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

This works because it used the cacheline better.

By switching the loops, the code reads data in its order. When the processor loads a cache line for the first number, the next numbers are already inside it. This means the program uses the whole cache line immediately, instead of constantly fetching new lines from slow memory and only working with a single item from each line.