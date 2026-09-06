# Question 2: 0/1 Knapsack Problem
## Problem Statement
Implement the 0/1 Knapsack problem using Dynamic Programming. Given n items with their weights and profits and a knapsack of capacity W, determine the maximum profit that can be obtained.
## Analysis
* **Time Complexity:** $O(N \cdot W)$ where $N$ is the number of items and $W$ is the capacity. The nested loop fills a 2D matrix of these dimensions.
* **Space Complexity:** $O(N \cdot W)$ required to maintain the 2D DP tabulation table.