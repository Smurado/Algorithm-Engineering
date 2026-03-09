# Topic

What do the metrics latency and throughput tell you about
the performance of an intrinsic function?

## Latency

Latency is the time needed to calculate and make the result of an operation available. It is measured in clock cycles.

**As an example:** An operation with a latency of 10 means that the CPU needs 10 clock cycles until the result is available.

## Throughput

Throughput measures the amount of time, again in clock cycles, required to start the next intrinsic operation of the same kind.

**As an example:** An operation with a throughput of 0.5 means that 2 operations can be started in one clock cycle.

## Impact on performance

The impact on performance is as follows:
The ability to start multiple operations in one clock cycle is called "instruction-level parallelism".
This allows the CPU to start multiple independent operations one after the other. After a while, the operational results become available. 
Once the first calculation finishes, the next ones follow in quick succession, effectively hiding the high latency. In loops, this is heavily utilized through a technique called "software pipelining".