# Topic

Discuss Donald Knuth’s original quote about premature
optimization. What is your opinion?

# Opinion

Donald Knuth is absolutely right with his observation. In practice, agile methodologies like Scrum are often implemented in a way that leaves little room for refactoring, as the focus is on delivering features sprint by sprint. Developers are expected to produce correct, optimized software right from the start, while also picking the correct architecture model for the task. 

If one picks a heavy architecture for the code right from the start of the project, the project might be doomed. Studies estimate that a significant portion of enterprise codebases consists of boilerplate and infrastructure code that doesn't directly contribute to business logic, instead of building a minimal viable product first and seeing if the project is even worth putting more time into. The same principle applies to performance: instead of optimizing before knowing where the actual bottleneck is, one should first build a working version and then use a profiler to identify the critical 3%.

This could also explain why the percentage of projects that fail because of software is rising.

His last statement that compilers should tell the programmer which part is used the most could be wrong. My first intuition is that I would want the compiler to be as lightweight as possible, but I have too little experience to say if this is a good idea or not.