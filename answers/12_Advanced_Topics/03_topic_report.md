# Topic

Non-Uniform Memory Access (NUMA)

## Report

In this report, I want to research more about NUMA. NUMA is a computer architecture design. The difference compared to normal Uniform Memory Access architectures is the existence of multiple memory banks for a CPU. By utilizing this, the CPU's latency is reduced. Below is a table that shows the main differences between both designs.


| Feature | UMA (Uniform Memory Access) | NUMA (Non-Uniform Memory Access) |
| :--- | :--- | :--- |
| **Basic Concept** | All processors share the same physical memory. | Memory is distributed across specific nodes (processors), but remains logically shared. |
| **Access Time** | **Equal.** Every processor takes the same amount of time to access any memory location. | **Variable.** Fast access to local memory; slower access to remote memory (attached to other CPUs). |
| **Architecture** | SMP (Symmetric Multiprocessing). Uses a single system bus for all cores. | Distributed Shared Memory. Uses a high-speed interconnect (e.g., QPI, Infinity Fabric) between nodes. |
| **Scalability** | **Low.** Performance degrades as more CPUs are added due to bus contention/bottlenecks. | **High.** Adding processors also adds local memory bandwidth, reducing bottlenecks. |
| **Programming** | **Simpler.** The developer does not need to worry about where data is physically stored. | **Complex.** Requires thread affinity and data placement optimization to ensure threads run near their data. |
| **Typical Usage** | General-purpose desktops, laptops, low-end servers. | High-performance computing (HPC), enterprise servers, supercomputers. |

The main selling point of NUMA is its scalability. The fact that each processor has its own local memory ensures that one can add more processors without the shared data bus becoming a bottleneck.