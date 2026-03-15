# Topic
### Read "What every systems programmer should know about concurrency."

## 1. Instruction Ordering

The first thing I found particularly interesting is the fact that on modern systems, it is not trivial to
guarantee that commands are executed in their intended order. I always assumed that it is hard to parallelize an
application, but not that hardware design itself doesn't guarantee that instructions within the same function are
executed in the specified order. It is really mind-blowing that so much happens under the hood without 
the programmer knowing, just to speed up the system or a given task.
This also explains why constructs like memory barriers exist, because without them, even simple flag-based synchronization between threads can silently break.

## 2. Heisenbugs – "hc svnt dracones"

Another thing I found very interesting to read is the section called "hc svnt dracones".
This section explains the principle of Heisenbugs and serves as a reminder that you don't always need to overengineer
certain aspects of a program. Sometimes, a simpler default implementation is enough to produce fewer bugs and requires
less intensive testing. It also provides some example questions that one should seriously take into consideration 
when designing a concurrent system.
This resonated with me because in practice, using well-tested primitives like mutexes is often safer and more maintainable than attempting clever lock-free designs that are nearly impossible to verify.