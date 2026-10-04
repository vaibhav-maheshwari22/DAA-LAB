# Q6: Element Uniqueness

## Objective
To implement a method in C to check if there are any duplicates among 'n' randomly generated numbers and derive a conclusion regarding the algorithm's efficiency for sufficiently large values of 'n'.

## Approach & Implementation Logic
A brute-force approach to check for duplicates would require comparing every element against every other element using nested loops. This yields a time complexity of O(n^2). 

To optimize this, I utilized a sort-and-scan approach:
1. **Sorting:** The array of random numbers is first sorted using C's highly optimized built-in `qsort` function. This step takes O(n log n) time.
2. **Linear Scan:** Once sorted, any duplicate elements will inherently be adjacent to each other. A single linear loop O(n) iterates through the array checking if `arr[i] == arr[i+1]`.

## Input & Output
*   **Input:** An array of `n = 1000` internally generated random integers bounded between 0 and 4999.
*   **Output:** The terminal prints the value and indices of the first detected duplicate, or a message stating no duplicates were found.

## Conclusion
For a sufficiently large value of 'n', the method of sorting before searching is vastly superior. The overall time complexity of this approach is dominated by the sorting step, making it **O(n log n)**. This prevents the severe performance bottlenecks and potential Time Limit Exceeded (TLE) issues that an O(n^2) brute-force algorithm would face when processing large datasets.