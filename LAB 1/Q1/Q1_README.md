# Q1: Order of Growth Analysis

## Objective
To arrange a given set of mathematical functions in increasing order of asymptotic growth for sufficiently large values of 'n'.

## Approach & Implementation Logic
The objective is achieved through a two-step process:
1. **Data Generation (C Program):** A C program calculates the exact values of the given functions. I used a loop for `n` from 1 to 40. I stopped at 40 because exponential functions (like 3^n) grow too fast and can cause overflow errors if 'n' is too large. The calculated values are written to a CSV file (`q1_data.csv`).
2. **Data Visualization (Python Script):** A Python script uses the `csv` and `matplotlib` libraries to read the generated data and plot it. 

### Why a Logarithmic Scale?
The plot uses a logarithmic scale on the Y-axis. This was necessary because the growth rates of the given functions vary drastically. If plotted on a standard linear scale, exponential functions would completely overshadow logarithmic and smaller polynomial functions, making them appear as a flat line at the bottom of the graph.

## Input & Output
*   **Input:** The C program implicitly generates values for 'n' from 1 to 40.
*   **Output:** 
    * `q1_data.csv`: Contains the computed values.
    * `q1_graph.png`: A log-scale graph visually demonstrating the comparative growth rates.

## Conclusion (Final Order of Growth)
Based on asymptotic analysis and validated by the generated plot, the functions arranged in increasing order of growth for sufficiently large 'n' are:

1. log₂(n)
2. 12√n
3. 50n^(0.5)
4. n^(0.51)
5. (2^32)n
6. n log₂(n)
7. n² - 324
8. 100n² + 6n
9. 2n³
10. n^log₂(n)
11. 3^n