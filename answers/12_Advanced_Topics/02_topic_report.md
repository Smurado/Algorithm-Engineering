# Topic 

General-Purpose Computing on Graphics Processing Units

## Report

For this section, I would like to research a little more about the different frameworks for programming the GPU to do certain tasks. I have heard about them in the past, but I want to know what they can do best and why they exist in the first place.

- **OpenCL:**
    An open standard for parallel programming across different hardware platforms (CPUs, GPUs, FPGAs). 
    It offers maximum portability and flexibility but is more complex to implement. It can be a bit slower than solutions from the manufacturers themselves.

- **Nvidia CUDA:**
    A proprietary platform made by Nvidia for, obviously, Nvidia GPUs. 
    Today it is heavily used for AI and scientific workloads. As it has been years in the making, the ecosystem is very refined, but the user is completely dependent on Nvidia cards.

- **Metal:**
    This is Apple's proprietary Low-Level-API for graphics and compute load on the Apple platform, mainly iOS and macOS. It is highly optimized for Apple Silicon and offers direct hardware access with minimal overhead.
    
- **Vulkan:**
    Is a platform independent Low-Level-API for 3D graphics and compute. It offers the most direct access to the GPU and minimizes driver overhead. But it is also one of the hardest APIs to work on as it requires a lot of code to be written.
    