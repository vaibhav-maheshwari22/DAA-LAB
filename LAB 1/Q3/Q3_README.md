# Q3: Performance Analysis of Bubble Sort

## Objective
To implement two distinct versions of the bubble sort algorithm for randomized data sequences and analyze their efficiency by plotting the number of comparisons. The two versions are:
1. An optimized bubble sort that terminates if the array is sorted before the (n-1)th pass.
2. A strict bubble sort that always completes the (n-1)th pass regardless of whether the array is already sorted.

## Approach & Implementation Logic
The project uses a two-step pipeline consisting of data generation in C and visualization in Python:

1. **Algorithm Implementation (C Program):** Two distinct functions are created. The optimized version introduces a boolean flag (`swapped`) to monitor passes; if a complete pass occurs without any elements being swapped, the algorithm breaks out of the loop early. The strict version relies on standard nested loops. Memory is dynamically allocated for arrays of increasing sizes (from 10 up to 1,000 elements) and populated with random integers. The total comparisons for both algorithms are computed and exported to a CSV file (`q3_data.csv`).
2. **Data Visualization (Python Script):** A Python script utilizes the native `csv` module to read the generated data. It then leverages `matplotlib` to plot the number of comparisons against the array size, clearly illustrating the performance divergence between the two implementations.

## Input & Output
*   **Input:** Randomly generated arrays of predefined sizes (10, 50, 100, 200, 300, 500, 800, and 1000 elements).
*   **Output:** 
    * `q3_data.csv`: A structured file containing the array sizes alongside their respective comparison counts for both algorithms.
    * `q3_graph.png`: A line graph visually contrasting the efficiency of the optimized early-exit method against the strict full-pass method.