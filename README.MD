# Design and Analysis of Algorithms (DAA) - Laboratory

Welcome to my DAA Lab repository. This repository serves as a comprehensive record of the algorithms and data structures implemented during the lab sessions. It focuses not just on writing the code, but on empirically validating theoretical asymptotic bounds using dynamic data generation, comparison tracking, and graphical visualization.

## 👤 Author Profile

| Field          | Details                                  |
| :------------- | :--------------------------------------- |
| **Name**       | Vaibhav Maheshwari                       |
| **Student ID** | b125136                                  |
| **Branch**     | Computer Science and Engineering (CSE-B) |
| **Institute**  | IIIT Bhubaneswar                         |

## 🛠️ Tech Stack

- **Algorithm Implementation:** C Programming Language (Standard Library only)
- **Data Visualization:** Python 3 (Matplotlib, Pandas)
- **Data Export:** CSV (Comma Separated Values)

---

## 📂 Repository Structure & Lab Index

| Lab                                  | Focus Area                                                                       | Questions |
| :----------------------------------- | :------------------------------------------------------------------------------- | :-------: |
| **[LAB 1](./LAB%201)**               | Growth of functions, empirical analysis, sorting fundamentals                    |     6     |
| **[LAB 2](./LAB2)**                  | Data structure trade-offs, divide & conquer, recurrences                         |     3     |
| **[LAB 3](./LAB%203)**               | Advanced Divide & Conquer, matrix operations, loop invariants                    |     6     |
| **[LAB 4](./LAB%204)**               | Applications of sorting, sweep-line algorithms, binary search integration        |     6     |
| **[LAB 5](./LAB%205)**               | Order statistics without sorting, randomized file I/O                            |     4     |
| **[LAB 6 1](./LAB%206/LAB%206%201)** | Array/Matrix operations, FFT convolution, sorting via reversals                  |     4     |
| **[LAB 6 2](./LAB%206/LAB%206%202)** | Dynamic Programming algorithms and state tabulation                              |     4     |
| **[LAB 7](./LAB%207)**               | Puzzle-based algorithms, combinatorial state spaces, advanced DP & sweep-line    |     7     |
| **[LAB 8](./LAB%208)**               | Dynamic Programming, Recursion, DP state reconstruction, open-problem simulation |     9     |
| **[LAB 9](./LAB%209)**               | Greedy algorithms, heap-based scheduling, prefix codes, open-problem conjecture  |    10     |

---

## 📖 Detailed Lab Breakdown

### Lab-01: Growth Rates & Simulation

Contains C programs for algorithm logic and Python scripts for plotting performance graphs based on the generated data.

- **Q1: Order of Growth Analysis** - Mathematical function growth comparison using logarithmic scales.
- **Q2: Fair vs Biased Coin Simulation** - Probability simulation using standard C library generators.
- **Q3: Performance Analysis of Bubble Sort** - Comparing time complexities of an optimized early-exit bubble sort against a strict full-pass bubble sort.
- **Q4: Towers of Hanoi Simulation** - Recursive logic implementation and tracking exponential $O(2^n)$ move growth.
- **Q5: Find the Partition Point** - Implementing $O(\log n)$ Binary Search to find transition points in a sorted boolean array.
- **Q6: Element Uniqueness** - Optimizing duplicate detection from $O(n^2)$ brute force to $O(n \log n)$ using Quick Sort.

### Lab-02: Data Structures & Master Theorem

Focuses on advanced data structure operations, recurrence relations, and optimized merging techniques.

- **Q1: Dictionary Operations Analysis** - Benchmarking the worst-case asymptotic running times of 7 primary operations across 6 fundamental data structures (Arrays, SLLs, DLLs - sorted and unsorted).
- **Q2: Merge Sort (2-Way vs Modified 3-Way)** - Implementing and comparing the practical execution time of standard 2-Way Merge Sort $O(n \log_2 n)$ against a modified 3-Way Merge Sort $O(n \log_3 n)$.
- **Q3: Merging K Sorted Arrays** - Evaluating the massive performance gap between Sequential Merging $O(n \cdot k^2)$ and an optimized Divide & Conquer Merging strategy $O(n \cdot k \log_2 k)$.

### Lab-03: Advanced Divide & Conquer

Splitting problems efficiently, analyzing trade-offs, and discharging mathematical proofs at runtime.

- **Q1: Binary vs Ternary Search** - Validating that $O(\log_2 n)$ is strictly better than $O(\log_3 n)$ by tracking actual element comparisons.
- **Q2: Search the Defective Coin** - Using a strict 2-way D&C approach to find a defective coin in exactly $O(\log_2 n + c)$ weighings.
- **Q3: Max and Min using D&C** - Finding both extremes of an array while mathematically proving the $3n/2 - 2$ comparison bound.
- **Q4: Strassen's Matrix Multiplication** - Achieving $O(n^{2.81})$ time complexity using 7 half-size products instead of the naive 8.
- **Q5: Multiplying Special-Pattern Matrices** - Utilizing structural matrix symmetry to collapse multiplications into a strictly $O(n^2)$ D&C approach.
- **Q6: Selection Sort & Loop Invariants** - Dynamically asserting initialization, maintenance, and termination invariants while proving $\Theta(n^2)$ runtime for best, worst, and average cases.

### Lab-04: Applications of Sorting

Focuses on using sorting as a foundational step to optimize complex search, matching, and overlapping interval problems.

- **Q1: Stable Color Sort** - Achieving an $O(n)$ stable sort using bucket categorization to group items by color without disrupting their initial numerical order.
- **Q2: Two Set Target Sum** - Reducing a brute-force $O(n^2)$ pair search to $O(n \log n)$ using `qsort` and binary search across two distinct sets.
- **Q3: K-Sum Problem** - Implementing a generalized recursive sweep combined with binary search to find a target sum among $k$ elements in $O(n^{k-1} \log n)$ time.
- **Q4: Party Peak Attendance** - Utilizing a sweep-line algorithm to process entry and exit events in $O(n \log n)$ time to find the maximum simultaneous overlaps.
- **Q5: Merge Overlapping Intervals** - Sorting intervals by start times to merge continuous overlapping ranges in $O(n \log n)$ time.
- **Q6: Point in Maximum Intervals** - Applying endpoint event sorting to identify a single coordinate present in the maximum number of intervals in $O(n \log n)$ time.

### Lab-05: Order Statistics & File I/O Sorting

Focuses on finding elements without full sorting using partition-based selection, and handling file operations with randomized data generation.

- **Q1: Find Median Without Sorting** - Utilizing the Quickselect algorithm to find the exact median in $O(N)$ average time with manual user input validation.
- **Q2: Find K'th Smallest Element** - Extending the Quickselect partitioning logic to find the $K^{th}$ order statistic in $O(N)$ average time.
- **Q3: Quick Sort with File I/O** - Generating $N$ random elements, storing them in a file, and applying in-place Quick Sort in $O(N \log N)$ expected time before writing the validated output back to disk.
- **Q4: Heap Sort with File I/O** - Implementing an $O(N \log N)$ worst-case Heap Sort on randomly generated file data and dynamically validating the sorted output.

### Lab 6 1: Advanced Operations & FFT

Focuses on analyzing worst-case bounds for foundational structures, finding $O(n \log n)$ convolution limits, and executing mathematical sorting models.

- **Q1: 1D Array Operations** - Analyzing and implementing strictly bounded algorithms for 9 distinct array operations, including QuickSelect median and randomized partitioning.
- **Q2: 2D Matrix Operations** - Executing in-situ transposition, $O(n^3)$ determinant Gaussian elimination, and power iteration for eigenspaces on square matrices.
- **Q3: Vector Convolution (FFT)** - Overcoming the $O(n \cdot m)$ convolution bottleneck using a Fast Fourier Transform Divide & Conquer approach to achieve $O(n \log n)$ time.
- **Q4: Sorting via Reversals** - Mathematically proving a $\le 2n$ reversal bound and designing a block-rotation Merge Sort to achieve an $O(n \log^2 n)$ operation cost.

### Lab 6 2: Dynamic Programming

Focuses on solving optimization problems by breaking them down into overlapping subproblems and tabulating state results to eliminate redundant recursive calls.

- **Q1: Nth Fibonacci Number** - Implementing an $O(N)$ dynamic programming approach to compute Fibonacci numbers, optimizing away the exponential recursive overhead.
- **Q2: 0/1 Knapsack Problem** - Using a 2D DP table to determine the maximum profit within a given weight capacity in $O(N \cdot W)$ time and space.
- **Q3: Longest Common Subsequence (LCS)** - Finding the longest common subsequence between two strings and reconstructing the exact sequence path in $O(M \cdot N)$ time.
- **Q4: Matrix Chain Multiplication** - Determining the optimal parenthesization of $N-1$ matrices to minimize total scalar multiplications in $O(N^3)$ time using DP memoization limits.

### Lab-07: Advanced Algorithm Applications & Puzzles

Focuses on solving classic mathematical puzzles, exploring game-theoretic parity, and implementing optimized DP and sweep-line algorithms.

- **Q1: Invert the Coin-Triangle** - Deriving an optimal geometric overlap compact formula $\lfloor n(n+1)/6 \rfloor$ to flip a coin triangle in $O(1)$ time.
- **Q2: Super Egg Testing Experiment** - Implementing a generalized $O(E \cdot F^2)$ DP solution to determine the critical threshold floor in the worst case for $E$ eggs and $F$ floors.
- **Q3: Reve's Puzzle (4-Peg Hanoi)** - Applying the Frame-Stewart divide-and-conquer strategy to move 8 disks in exactly 33 moves, scaling in $O(2^{\sqrt{2n}})$ time.
- **Q4: Security Switches** - Modeling switch toggle dependencies using Gray code and the Baguenaudier recursion to deactivate $n$ switches in $\Theta(2^n)$ minimum moves.
- **Q5: Hitting a Moving Target** - Designing a deterministic two-phase parity sweep algorithm guaranteeing target interception on $n$ spots within $2n-4$ shots.
- **Q6: The Best Time to be Alive** - Using an $O(N \log N)$ sweep-line algorithm with a death-before-birth tie-breaking policy to find the peak concurrent lifespan year.
- **Q7: Matrix Chain Multiplication (MCM)** - Implementing the $O(n^3)$ dynamic programming parenthesization table to minimize scalar operations and reconstructing the exact associative order.

### Lab-08: Dynamic Programming & Recursion

Focuses on the core DP paradigms — 1D/2D tabulation, subsequence reconstruction, edit operations, tree optimisation — and a modular simulation of the Collatz Conjecture, one of the most famous open problems in mathematics.

- **Q1: Minimum Coin Change** - 1D DP `dp[i] = min(dp[i], 1 + dp[i-c])` in $O(n \cdot V)$ time with coin-level traceback via a `last[]` array.
- **Q2: Coin Change — Total Ways** - Counting distinct combinations (order-independent) in $O(n \cdot V)$ time via outer-loop-over-coins DP `dp[j] += dp[j-c]`.
- **Q3: Longest Common Subsequence** - Computing LCS length of two strings in $O(m \cdot n)$ time via a 2D DP matrix, and reconstructing the actual subsequence string by diagonal backtracking.
- **Q4: Longest Increasing Subsequence** - Finding the longest strictly increasing subsequence in $O(n^2)$ time with `parent[]`-based reconstruction of the actual subsequence.
- **Q5: Maximum Sum Increasing Subsequence** - Extending LIS to track maximum sum instead of length, in $O(n^2)$ time, with full subsequence reconstruction.
- **Q6: Edit Distance with Traceback** - Minimum insert/delete/substitute operations via 2D DP in $O(m \cdot n)$ time, printing step-by-step transformation (Keep / Insert / Delete / Substitute).
- **Q7: Rod Cutting with Reconstruction** - Maximising revenue via `revenue[j] = max(price[i-1] + revenue[j-i])` in $O(n^2)$ time, with piece-length reconstruction via `first_cut[]`.
- **Q8: Optimal Binary Search Tree** - CLRS 3-loop DP computing minimum expected search cost in $O(n^3)$ time using `e`, `w`, and `root` tables, with full BST structure reconstruction including dummy keys.
- **Q9: Collatz Conjecture Analysis** - Modular C program simulating $T(n) = n/2$ or $3n+1$ until reaching 1, using `unsigned long long` and dynamic `realloc` buffers. Supports single-value and interval $[a, b]$ analysis with peak tracking.

### Lab-09: Greedy Algorithms & Heap-Based Scheduling

Focuses on greedy choice properties, exchange-argument optimality, priority-queue driven scheduling, and a landmark open-problem simulation (the Greedy Superstring Conjecture, disproved in September 2026).

- **Q1: Fractional Knapsack with Deterioration Rate** - Subset DP over all $2^n$ masks of fully consumed items with one fractional item on top, in $O(n \cdot 2^n)$ time, using the integrated density $\text{density}_i(t) = v_i/w_i - \lambda_i \cdot t$.
- **Q2: Huffman Coding** - Building a minimum-length prefix code via a frequency-keyed min-heap in $O(n \log n)$ time, then canonicalising the codebook by $(\text{length}, \text{symbol})$ for direct decodability without transmitting the tree.
- **Q3: Minimum Refuelling Stops** - Reverse greedy sweep across stations with a max-heap of passed-but-unused fuel amounts, achieving the minimum stop count in $O(n \log n)$ time.
- **Q4: Minimum Cost to Connect Sticks** - Huffman-style greedy that always merges the two shortest current sticks via a min-heap, minimising total join cost in $O(n \log n)$ time.
- **Q5: Candy Distribution (Bi-directional Slope Greedy)** - Two independent sweeps (left-to-right and right-to-left) with $\text{candies}[i] = \max(\text{left}[i], \text{right}[i])$, in $O(n)$ time.
- **Q6: Reorganise String with K-Distance Apart** - Greedy placement by highest remaining frequency under a cooldown check $i - \text{last}[c] \ge K$, running in $O(n \cdot 256)$ time.
- **Q7: Minimise Deviation in Array** - Normalising all odd values by doubling, then repeatedly halving the current even maximum via a max-heap, in $O(n \log M \log n)$ time.
- **Q8: Minimum Number of Meeting Rooms** - Sweep-line over meetings sorted by start time with a min-heap of active end times, reusing freed rooms on demand in $O(n \log n)$ time.
- **Q9: Optimal Alphabetic Binary Tree (Interval DP)** - Computing the minimum weighted path length $\sum w_i \cdot \text{depth}(i)$ while preserving leaf order via $O(n^3)$ interval DP, with full alphabetic-tree reconstruction.
- **Q10: Greedy Superstring Conjecture (Open Problem)** - Implementing the maximum-overlap greedy merger for the NP-hard Shortest Superstring Problem in $O(n^3 \cdot T^2)$ time. The long-standing 2-approximation conjecture was disproved by a September 2026 arXiv paper showing the ratio can reach $\tfrac{9}{4}$.
