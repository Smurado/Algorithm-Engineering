# Topic

Read the article Intel MMX for Multimedia PCs.
https://dl.acm.org/doi/pdf/10.1145/242857.242865
Discuss two things you find particularly interesting.

## Topic 1

### The reason for the introduction of MMX.

I find it particularly interesting, that the reason for the MMX-Introduction was the underutilization of the 64 bit data width the processor could handle. Which in terms of performance meant, that the processor could handle more and speed up tasks like multimedia, communications, and other numeric-intensive applications.

Whats very funny about this is, that at the time those things were not as smooth and self-evident as we grant them today. Since then approximalty 30 years have passed and nowadays we dont even think about the fact, that multimedia was a challenge for PCs in the past.

## Topic 2

### MMX Read/Write Stage

Another thing i found very interesting is the fact, that the engeneers also changed the pipeline.
Because they made the special stages for reading and writing in the pipeline seperating on from another when handling MMX operands.

This allows to perform a calculation with one perand in memory and the other in a register to complete in just one clock cycle. 
In contrast to this old Pipelines required two consecutive cycles.
This effectifly halves the number of needed clock cycles.