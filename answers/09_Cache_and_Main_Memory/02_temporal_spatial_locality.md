# Topic

Explain why temporal locality and spatial locality can
improve program performance.

# Answer

Both **temporal locality** and **spatial locality** describe ways in which we can speed up the program by minimizing main memory access. As we have learned, this is one of the main reasons why computation is slowed down (latency).

**Temporal locality** can improve the program's speed by reusing the data from the cache, as we might need it again in the near future. Since we keep this data in the cache instead of fetching it from memory, the latency is significantly lower.

**Spatial locality** means that if data is accessed, the data nearby is likely to be accessed as well for a following operation. Therefore, it is loaded automatically. So, the CPU does not need to wait for the data to arrive as it is already loaded.

**Summary:** Both localities try to minimize the amount of times data needs to be loaded from memory.