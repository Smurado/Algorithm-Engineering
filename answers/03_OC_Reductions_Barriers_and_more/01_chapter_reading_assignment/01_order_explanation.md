# Question

When run with one thread per logical core, threads from
Listing 3.1 display their numbers randomly, while those from
Listing 3.2 show them in the same order. Explain why.

# Reasoning

The 'Hello World' program is a very simple program. 
All a thread has to do is to write out 'hello world' and its corresponding number.
This can be done very quickly by the threads. Therefore, the output order is mostly determined by the OS thread scheduling, resulting in a random sequence.

In the Fibonacci program, on the other hand, each number is calculated by a different thread. 
The larger the number, the more work a thread has to do.
For example, _F3_ is 2, while _F15_ is already 610.
Therefore, it is highly unlikely that a thread calculating a higher number will finish and print before a thread calculating a lower one, as it takes significantly more time to compute.