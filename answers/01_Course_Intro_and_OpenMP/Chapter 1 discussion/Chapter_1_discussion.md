# Discussion of Two Topics from the Book "A Tour of Computer Systems"

## Topic 1: The GNU Project

I find it particularly interesting that the GNU Project tried to create its own operating system.
I always thought the project was about spreading the idea of open source in the development of new software.
But the idea of a whole UNIX-based operating system, with the freedom to do with it whatever the project 
wants, sounds very cool! As an example, Microsoft had to implement functionality to fulfill the 
'Security Technical Implementation Guides', which were forced on Microsoft by the Pentagon in order for Windows to be 
allowed in classified networks. 

It seems like the original developers of GNU were all about the freedom to speak freely and remain anonymous.
I really do wonder why they were never able to create their own kernel. Linux, on the other hand, benefits greatly from the
tools provided by GNU. With it, the first foundation for open source was laid.

## Topic 2: Cache/Storage Hierarchy

Another topic that was interesting to me is the storage pyramid (Figure 1.9). 
Even though I already knew about the concept of the pyramid, it is interesting to see that the different levels use 
cache lines from the levels below, which makes perfect sense.

It is crazy to think that the first PCs only had some kilobytes of memory and nowadays a system with 32 GB is
becoming normal. The progress of technical evolution not only made memory bigger, but also cache gets significantly 
larger with each iteration of a new system. 

An example for this would be the first introduction of L3 cache in a consumer CPU in 2003 with the 
Intel Pentium 4 Extreme Edition, which only had 2 MB of L3 cache. Modern 'gaming' CPUs like the AMD Ryzen 7 9800X3D
have a stacked cache on the CPU die and by this achieve 96 MB L3 cache on an 8-core CPU.