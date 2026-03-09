# Topic

Read the article Intel MMX for Multimedia PCs.
https://dl.acm.org/doi/pdf/10.1145/242857.242865
Discuss two things you find particularly interesting.

## Topic 1

### The reason for the introduction of MMX

I find it particularly interesting that the reason for the introduction of MMX was the underutilization of the 64-bit data width the processor could handle. In terms of performance, this meant that the processor could theoretically handle more data at once and speed up tasks like multimedia, communications, and other numeric-intensive applications.

What is very funny about this is that, at the time, those things were not as smooth and self-evident as we take them for granted today. Since then, approximately 30 years have passed, and nowadays we don't even think about the fact that basic multimedia playback was a challenge for PCs in the past.

## Topic 2

### MMX Read/Write Stage

Another thing I found very interesting is the fact that the engineers also changed the pipeline.
They decoupled the specific stages for reading and writing in the pipeline, making them independent from one another when handling MMX operands.

This allows an instruction performing a calculation with one operand in memory and the other in a register to complete in just one clock cycle. 
In contrast, older pipelines required two consecutive cycles for such operations.
This effectively halves the number of needed clock cycles.