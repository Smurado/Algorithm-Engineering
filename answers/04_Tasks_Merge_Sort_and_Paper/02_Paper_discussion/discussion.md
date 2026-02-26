# Topic
### Read What every systems programmer should know about concurrency.

The First thing I found particularly interesting is the fact, that on modern Systems it is not that trivial to
guarantee, that the commands are executed in the designed order. I always assumed that it is hard to parallelize an
application. But not that it is also by design of the Hardware not guaranteed that things in the same function get
executed in the specified order. It is really mindblowing that so much is working together under the hood without 
the programmers knowing just to speed up the system or a given task.

One other thing that I found very nice too read is the section called: 'hc svnt dracones'.
This one explaines the principle of Heisenbugs and should be a reminder that you don't always need to overengineer
certain aspects of a program. Sometimes the default implementation is enough to have fewer bugs and be able to test less
intensive. It also gives some examples in questions which one should really take into consideration.