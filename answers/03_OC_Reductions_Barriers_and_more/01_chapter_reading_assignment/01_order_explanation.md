# Question

When run with one thread per logical core, threads from
Listing 3.1 display their numbers randomly, while those from
Listing 3.2 show them in the same order. Explain why.

# Reasoning

The Hello world program is a very simple program. 
All a thread has to do is to write out 'hello world' and its corresponding number.
This can be done very fast by the thread. So it is highly likely that some threads might be faster than others.

The Fibonacci program on the other hand, each number gets calculated by a different thread. 
As the numbers increase, the more work a thread has to do.
For example, _F3_ is 2, while _F15_ is already 610.
So it is highly unlikely that a higher number gets output by a thread before a lower one as it takes much longer to calculate.