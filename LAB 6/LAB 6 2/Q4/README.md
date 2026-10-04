# Question 4: Matrix Chain Multiplication
## Problem Statement
Write a program to implement Matrix Chain Multiplication using Dynamic Programming. Given the dimensions of N-1 matrices in an array arr[], determine the minimum number of scalar multiplications required.
## Analysis
* **Time Complexity:** $O(N^3)$. The algorithm utilizes three nested loops: one for chain length, one for starting index, and one for testing every possible split point $k$.
* **Space Complexity:** $O(N^2)$ to store the scalar multiplication costs in a 2D DP matrix.