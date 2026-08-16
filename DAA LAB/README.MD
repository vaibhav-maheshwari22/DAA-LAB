# Design and Analysis of Algorithms (DAA) - Laboratory 

Welcome to my DAA Lab repository. This repository serves as a comprehensive record of the algorithms and data structures implemented during the lab sessions. It focuses not just on writing the code, but on empirically validating theoretical asymptotic bounds using dynamic data generation, comparison tracking, and graphical visualization.

## 👤 Author Profile

| Field | Details |
| :--- | :--- |
| **Name** | Vaibhav Maheshwari |
| **Student ID** | b125136 |
| **Branch** | Computer Science and Engineering (CSE-B) |
| **Institute** | IIIT Bhubaneswar |

## 🛠️ Tech Stack
* **Algorithm Implementation:** C Programming Language (Standard Library only)
* **Data Visualization:** Python 3 (Matplotlib, Pandas)
* **Data Export:** CSV (Comma Separated Values)

---

## 📂 Repository Structure & Lab Index

| Lab | Focus Area | Questions |
| :--- | :--- | :---: |
| **[Lab-01](./Lab-01)** | Growth of functions, empirical analysis, sorting fundamentals | 6 |
| **[Lab-02](./Lab-02)** | Data structure trade-offs, divide & conquer, recurrences | 3 |
| **[Lab-03](./Lab-03)** | Advanced Divide & Conquer, matrix operations, loop invariants | 6 |

---

## 📖 Detailed Lab Breakdown

### Lab-01: Growth Rates & Simulation
Contains C programs for algorithm logic and Python scripts for plotting performance graphs based on the generated data.
* **Q1: Order of Growth Analysis** - Mathematical function growth comparison using logarithmic scales.
* **Q2: Fair vs Biased Coin Simulation** - Probability simulation using standard C library generators.
* **Q3: Performance Analysis of Bubble Sort** - Comparing time complexities of an optimized early-exit bubble sort against a strict full-pass bubble sort.
* **Q4: Towers of Hanoi Simulation** - Recursive logic implementation and tracking exponential $O(2^n)$ move growth.
* **Q5: Find the Partition Point** - Implementing $O(\log n)$ Binary Search to find transition points in a sorted boolean array.
* **Q6: Element Uniqueness** - Optimizing duplicate detection from $O(n^2)$ brute force to $O(n \log n)$ using Quick Sort.

### Lab-02: Data Structures & Master Theorem
Focuses on advanced data structure operations, recurrence relations, and optimized merging techniques.
* **Q1: Dictionary Operations Analysis** - Benchmarking the worst-case asymptotic running times of 7 primary operations across 6 fundamental data structures (Arrays, SLLs, DLLs - sorted and unsorted).
* **Q2: Merge Sort (2-Way vs Modified 3-Way)** - Implementing and comparing the practical execution time of standard 2-Way Merge Sort $O(n \log_2 n)$ against a modified 3-Way Merge Sort $O(n \log_3 n)$.
* **Q3: Merging K Sorted Arrays** - Evaluating the massive performance gap between Sequential Merging $O(n \cdot k^2)$ and an optimized Divide & Conquer Merging strategy $O(n \cdot k \log_2 k)$.

### Lab-03: Advanced Divide & Conquer
Splitting problems efficiently, analyzing trade-offs, and discharging mathematical proofs at runtime.
* **Q1: Binary vs Ternary Search** - Validating that $O(\log_2 n)$ is strictly better than $O(\log_3 n)$ by tracking actual element comparisons.
* **Q2: Search the Defective Coin** - Using a strict 2-way D&C approach to find a defective coin in exactly $O(\log_2 n + c)$ weighings.
* **Q3: Max and Min using D&C** - Finding both extremes of an array while mathematically proving the $3n/2 - 2$ comparison bound.
* **Q4: Strassen's Matrix Multiplication** - Achieving $O(n^{2.81})$ time complexity using 7 half-size products instead of the naive 8.
* **Q5: Multiplying Special-Pattern Matrices** - Utilizing structural matrix symmetry to collapse multiplications into a strictly $O(n^2)$ D&C approach.
* **Q6: Selection Sort & Loop Invariants** - Dynamically asserting initialization, maintenance, and termination invariants while proving $\Theta(n^2)$ runtime for best, worst, and average cases.

---
