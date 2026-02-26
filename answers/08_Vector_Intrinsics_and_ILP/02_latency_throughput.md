# Topic

What do the metrics latency and throughput tell you about
the performance of an intrinsic function?

## Latency

The latency is the time needed to calculate and to make a result of an operation available. It is measured in clock cycles.

**As an example:** An operation with a latency of 10 means, that the computer needs 10 clock cycles until a result is available.

## Throughput

The throughput measures the amount of time, again in clock cycles, to start the next intrinsic operation of the same kind.

**As an example:** An operation with a throughput of 0.5 means, that 2 operations can be startet in one clock cycle.

## Impact on performance

The impact on performance is the following:
The ability to start multiple operations in one clock cycle is called "instruction level parallelism".
This allows the CPU to start multiple independent operations one after the other and after a while the operation results are available. 
But once they start to get available, they come fast after each other, this hides the high latency and is called "software pipelining".