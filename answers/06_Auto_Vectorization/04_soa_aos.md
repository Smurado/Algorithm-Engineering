# Topic 
When would you prefer arranging records in memory as a
Structure of Arrays?

## Answer

Consider a database with 1000 employees. Each employee has a Name, an Age, and a Salary.

For **Array of Structures (AoS)**, the memory layout could look something like this:
**Memory:**
    `[Name, Age, Salary], [Name, Age, Salary] ...`

If we want to display the full information about employee number 142, an Array of Structures is perfect. Since all of their data is at the same memory location, it's a single, fast access that makes great use of spatial locality.

For **Structure of Arrays (SoA)**, the memory layout looks like this:
**Memory:** 
    * `Names:   [Name, Name, Name ...]`
    * `Ages:    [Age, Age, Age ...]`
    * `Salaries: [Salary, Salary, Salary ...]`

If we wanted to calculate the **total payroll of all employees**, we would prefer the Structure of Arrays (SoA). Because the `Salaries` are aligned tightly in memory without being interrupted by Names and Ages, we can use fast unit-stride memory access to simply load and add up all the entries using SIMD instructions. SoA is usually better when operating on specific fields across many records simultaneously.