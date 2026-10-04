# Question 3: Longest Common Subsequence (LCS)
## Problem Statement
Implement the LCS algorithm using Dynamic Programming. Given two strings, find the length of their longest common subsequence and display the subsequence.
## Analysis
* **Time Complexity:** $O(M \cdot N)$ where $M$ and $N$ are the lengths of the two strings. It involves filling a 2D matrix, followed by an $O(M+N)$ traversal to reconstruct the string.
* **Space Complexity:** $O(M \cdot N)$ for the 2D state matrix storing the lengths of subproblem sequences.