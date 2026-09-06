# Question 2: 2D Square Matrix Operations

## Problem Statement
Given square matrices with n rows and n columns, compute and analyze the worst-case computational complexity for standard algebraic matrix algorithms including addition, multiplication, determinants, and eigenspace properties[cite: 2].

## Algorithmic Approaches
1. **Addition & Zero/Symmetric Checks:** Requires linearly iterating through the 2D grid structure. Zero checks can exit early, but the worst-case requires a full pass.
2. **Multiplication:** Implemented using the standard naive 3-nested loop structure calculating dot products of rows and columns.
3. **Determinant:** Instead of the inefficient $O(n!)$ Laplace expansion, this program leverages **Gaussian Elimination** to reduce the matrix to upper triangular form, calculating the determinant as the product of the diagonal elements.
4. **In-situ Transpose:** Processes strictly the upper triangle of the matrix, swapping $A[i][j]$ with $A[j][i]$ to avoid allocating a secondary $n \times n$ array.
5. **Eigenvalue/Eigenvector:** Utilizes the **Power Iteration Method**. It repeatedly multiplies the matrix by a normalized vector to converge upon the dominant eigenvector, subsequently computing the Rayleigh quotient for the eigenvalue.

## Worst-Case Complexity Analysis
* **(i) Matrix Addition:** $O(n^2)$
* **(ii) Matrix Multiplication:** $O(n^3)$
* **(iii) Zero Matrix Check:** $O(n^2)$
* **(iv) Symmetric Matrix Check:** $O(n^2)$
* **(v) Determinant:** $O(n^3)$
* **(vi) Transposing in situ:** $O(n^2)$ (specifically bounding to $n(n-1)/2$ operations)
* **(vii) Eigenvalue/Eigenvector:** $O(k \cdot n^2)$ where $k$ represents the convergence iterations.