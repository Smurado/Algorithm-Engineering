# Topic 
When would you prefer arranging records in memory as a
Structure of Arrays?

## Answer

Given a database with 1000 employees. Each employee has a name, an age and a Salary.

For **Array of Structures** in Memory could look something like this.
**Memory:**
    `[Name, Age, Salary], [Name, Age, Salary] ...`

If we would want to display the informations about employee with the number 142. 
Since all thier info is at the same memory location, its a single, fast access.


For **Structure of Arrays** in Memory could look something like this.
**Memory:** 
    * `Names: [Name, Name, Name ...]`
    * `Ages: [Age, Age, Age ...]`
    * `Salaries: [Salary, Salary, Salary ...]`

If we wanted to know the **payroll of all employes** we would use Structure of Arrays as we could simply add up all the entries from the **Saleries** Array.