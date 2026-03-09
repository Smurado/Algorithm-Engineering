# Paper 

Read the paper: https://ieeexplore.ieee.org/document/7552037
Discuss two things you find particularly interesting.

## Discussion 1

### Topic

SSD-friendly application design

### Discussion

I found it quite interesting what goals the paper tries to achieve, namely improved application performance, increased SSD IO efficiency, and longer SSD life. They mention methods like: avoiding in-place update optimizations, separating hot data from cold data, and adopting compact data structures, which I want to explain.

- **Avoiding in-place update optimizations**
    SSDs cannot overwrite data like normal HDDs. They have to delete a whole block, which is slow and shortens the lifespan of the SSD. So it is better to append new data instead of modifying the old.

- **Separating hot data from cold data**
    As the method suggests, data that is stored over a long period of time should be stored independently from data that is changed frequently. This reduces the garbage collection overhead of the SSD.

- **Adopting compact data structures**
    Data should be as small as possible by, for example, compressing it. As SSDs have a limited lifecycle of their cells, the less they have to be used to write new data, the better.

As these things are not trivial, it is nice that such a paper gives hints to them and tries to guide new developers onto the right path in handling SSDs.

## Discussion 2

### Topic 

Use multiple threads on SSDs

### Discussion

A thing that I thought should be kept in mind is the parallelism of SSDs. The controller can handle multiple searches and reads in parallel, but it might still be treated as a single operation from the host's perspective. For example: Imagine a library with eight librarians. If we send only one person to fetch a book, wait for them to return, and then send the next person, seven librarians are just standing around doing nothing. But if we send eight requests at once, all librarians can search for books in different corridors simultaneously, finishing the job eight times faster.

Before this paper, I didn't think about this concept, but it's absolutely logical as there are no moving/mechanical parts anymore.
