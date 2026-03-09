# Topic

Name some characteristics of the instructions sets: SSE,
AVX(2) and AVX-512.

## SSE instruction set

The name stands for "Streaming SIMD Extensions".
The SSE instruction set has a vector length of 128 bits and uses the registers `xmm0` to `xmm15`. 
It has been used in nearly all modern processor architectures since 1999 and can thereby be used as a way to make a program platform-independent.
SSE supports integer and floating-point calculations and can be parallelized.


## AVX(2) instruction set

The AVX(2) instruction set is an extension of the AVX set and was launched in 2013.
AVX stands for Advanced Vector Extensions and has a vector length of 256 bits.
It also supports horizontal operations on the vector.
AVX(2) supports bit manipulation, doubles the amount of integer operations in one clock tick, and improves the broadcast and gather operations from the classic AVX.
Since Intel Alder Lake (2021), every Intel processor supports AVX(2) natively, even the Intel N100s.
On AMD's side, it is supported since the launch of the original Zen architecture in 2017.


## AVX-512 instruction set

The AVX-512 instruction set is an extension of the AVX(2) set and was launched in 2017.
This instruction set uses the registers `zmm0` to `zmm31`.
Its biggest difference is the support for even larger vector lengths of up to 512 bits.
It also doubles the number of available registers from 16 to 32.
Modern processors natively support AVX-512 in more consumer workloads.

**AMD** uses a clever trick, as they bundle two 256-bit units together to create support for the large instruction set. It has been supported on consumer chips since Zen 4 (Ryzen 7000).

For **Intel**, the situation is a bit more complicated. Since its switch to a hybrid architecture, P-Cores on Intel could theoretically fully support AVX-512, but E-Cores did not. Intel therefore disabled AVX-512 on consumer chips like Alder Lake, making its availability heavily dependent on the specific architecture generation and server focus.
