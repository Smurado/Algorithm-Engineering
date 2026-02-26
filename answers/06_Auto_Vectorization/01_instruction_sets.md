# Topic

Name some characteristics of the instructions sets: SSE,
AVX(2) and AVX-512.

## SSE instruction set

The name stand for "Streaming SIMD Extensions".
SSE instruction set has a vector length of 128-bit and uses the registers xmm0 to xmm15. 
It is used in nearly all mordern processor since 1999 architectures an can be thereby used as a way, to make a programm plattform independant.
SSE supports integer and floating-point-calculations and can be parallised.


## AVX(2) instruction set

The AVX(2) instruction set is an extension of the AVX set and was launched in 2013.
AVX stands for advanced vector extension and has a vector length of 256 bit.
It also supports horizontal operations on the vector.
AVX(2) supports bit manipulation, doubles the amout of integer operations in one tick and improves the boardcast- and gather- operations from the classic AVX.
Since Intel Alder Lake (2021) every Intel processor supports AVX(2) nativ even Intel N100's.
On AMD's side they are supported since the launch of the new Zen-Architecture in 2017.


## AVX-512 instruction set

The AVX-512 inscrution set is an extension to the AVX(2) set and it was launched in 2017.
The instcrution set hearby uses the Registers zmm0 - zmm31.
Its biggest difference is the support of even bigger vector lengts of up to 512-bit.
But it also doubles the number of available registers from 16 to 32.
Modern Processors since 2025 beginn to implement nativ support of AVX-512.

**AMD** uses a clever trick as they bundle two 256-bit units together to create support for the large instruction set. It is supported since Zen 5 (Ryzen 7000).

For **Intel** the situation is a bit more complicated. Since it's switch to a hypbrid architecture, P-Cores on Intel fully support AVX-512. E-Cores on the other hand didn't until it's reintroduction with their 13. and 14. gen.
E-Cores still dont support it nativly but they split up the large instruction into two 256bit segments.
