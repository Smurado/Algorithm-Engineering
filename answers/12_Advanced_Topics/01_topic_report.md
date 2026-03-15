# Topic

Static Schedules: OpenMP vs. C++ Threads

## Report

This topic really shows why OpenMP is a perfect tool to get in touch with parallelization in C++.
The threads code looks a lot scarier than the OpenMP code. It also highlights the key selling point of OpenMP, which is the ability to write your code first and parallelize it afterward, without needing a heavy focus on structuring the code in a specific way from the start. This is exactly how I handled my project: At first, I wrote the program to run on one thread, and I implemented the possibility for it to run on multiple threads later on. Of course, there were some problems initially, but as a developer, I only had to adjust minor details to achieve the speedup of parallelization.
However, C++ Threads offer more control and are better suited for task-based parallelism where different threads perform entirely different work, such as in producer/consumer patterns.