# Q4: Towers of Hanoi Simulation

## Objective
To simulate the solution to the Towers of Hanoi (ToH) problem using C, plot the total number of moves required for solving the problem of n-discs, and derive a conclusion regarding the algorithm's performance based on the obtained plot.

## Approach & Implementation Logic
The project utilizes a standard recursive approach to solve the ToH problem:
1. **Simulation (C Program):** The program calculates the total moves required for `n` discs ranging from 1 to 15. To accurately track moves across recursive function calls without relying on global variables, a pointer (`long long *moves`) is passed by reference. The results are logged into a CSV file (`q4_data.csv`).
2. **Visualization (Python Script):** A Python script reads the CSV data and generates a line plot using `matplotlib`, displaying the relationship between the number of discs and the required moves.

## Input & Output
*   **Input:** The number of discs `n` iterated from 1 to 15.
*   **Output:** 
    * `q4_data.csv`: Contains the raw values mapping `n` to the total calculated moves.
    * `q4_graph.png`: A visual representation of the growth curve.

## Conclusion
From the plot obtained, the curve rises sharply in a non-linear fashion. Mathematically, the data perfectly aligns with the formula (2^n - 1). Therefore, we can conclude that the recursive algorithm for the Towers of Hanoi has an exponential time complexity of O(2^n). For every additional disc added, the number of required moves essentially doubles, making it highly inefficient for large values of 'n'.