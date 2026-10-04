# DAA Lab 08 — Dynamic Programming & Recursion

![Language](https://img.shields.io/badge/Language-C-blue)
![Standard](https://img.shields.io/badge/Standard-C99-orange)
![Compiler](https://img.shields.io/badge/Compiler-GCC-green)
![Course](https://img.shields.io/badge/Course-DAA-purple)

**Course:** Design and Analysis of Algorithms (DAA)  
**Semester:** 3rd Semester — B.Tech (CSE-B)  
**Author:** Vaibhav Maheshwari (B125136)  
**Repository:** [DAA-LAB](https://github.com/vaibhav-maheshwari22/DAA-LAB)

---

## Overview

C implementations for all 9 problems from DAA Lab 08. Each program uses standard C (C99, GCC compatible), dynamic memory allocation, prints intermediate DP states, and includes reconstruction/traceback where required. Complexity analysis is written at the top of each `.c` file.

---

## File Structure
LAB 8/
├── README.md
├── q1_min_coin.c
├── q2_coin_ways.c
├── q3_lcs.c
├── q4_lis.c
├── q5_msis.c
├── q6_edit_distance.c
├── q7_rod_cutting.c
├── q8_obst.c
└── q9_collatz.c

---

## Problem Summary

| # | Problem | File | Time | Space |
|:-:|:--------|:-----|:----:|:-----:|
| 1 | Minimum Coin Change | [`q1_min_coin.c`](./q1_min_coin.c) | O(n·V) | O(V) |
| 2 | Coin Change — Total Ways | [`q2_coin_ways.c`](./q2_coin_ways.c) | O(n·V) | O(V) |
| 3 | Longest Common Subsequence | [`q3_lcs.c`](./q3_lcs.c) | O(m·n) | O(m·n) |
| 4 | Longest Increasing Subsequence | [`q4_lis.c`](./q4_lis.c) | O(n²) | O(n) |
| 5 | Max Sum Increasing Subsequence | [`q5_msis.c`](./q5_msis.c) | O(n²) | O(n) |
| 6 | Edit Distance + Traceback | [`q6_edit_distance.c`](./q6_edit_distance.c) | O(m·n) | O(m·n) |
| 7 | Rod Cutting + Reconstruction | [`q7_rod_cutting.c`](./q7_rod_cutting.c) | O(n²) | O(n) |
| 8 | Optimal BST | [`q8_obst.c`](./q8_obst.c) | O(n³) | O(n²) |
| 9 | Collatz Conjecture | [`q9_collatz.c`](./q9_collatz.c) | O(L(n)) | O(L(n)) |

---

## Problem Notes

**Q1 — Minimum Coin Change**  
`dp[i] = min(dp[i], 1 + dp[i-c])` for each coin `c ≤ i`. Extra `last[]` array used to trace which coins were used. Returns `-1` if unreachable.

**Q2 — Coin Change: Total Ways**  
Counts distinct combinations (order doesn't matter). Outer loop over coins, inner loop over amounts → gives combinations, not permutations. `dp[j] += dp[j-c]`.

**Q3 — Longest Common Subsequence**  
If `X[i-1] == Y[j-1]`: `dp[i][j] = dp[i-1][j-1] + 1`. Else: `max(dp[i-1][j], dp[i][j-1])`. Backtracks from `(m,n)` to reconstruct the LCS string.

**Q4 — Longest Increasing Subsequence**  
`dp[i] = 1 + max(dp[j])` for `j < i` with `A[j] < A[i]`. `parent[]` array stores the predecessor for reconstruction.

**Q5 — Maximum Sum Increasing Subsequence**  
Same as LIS but tracking sum: `msis[i] = A[i] + max(msis[j])` for `j < i` with `A[j] < A[i]`.

**Q6 — Edit Distance with Traceback**  
`dp[i][j] = 1 + min(delete, insert, substitute)` when characters differ. Traceback prints each step as Keep / Insert / Delete / Substitute in forward order.

**Q7 — Rod Cutting**  
`revenue[j] = max(price[i-1] + revenue[j-i])` for `1 ≤ i ≤ j`. `first_cut[]` array reconstructs the optimal piece lengths.

**Q8 — Optimal BST**  
Classic CLRS 3-loop DP: `e[i][j] = min(e[i][r-1] + e[r+1][j] + w[i][j])` over all `r ∈ [i,j]`. Prints `e`, `w`, `root` tables and final tree structure with dummy keys.

**Q9 — Collatz Conjecture**  
`T(n) = n/2` (even) or `3n+1` (odd), stop at 1. Uses `unsigned long long` to prevent overflow. Dynamic `realloc` buffer stores trajectory. Two modes: single value and interval `[a,b]`.

---

## Compilation & Execution

### Compile a single file

```bash
gcc -Wall -Wextra -std=c99 q1_min_coin.c -o q1
./q1
```

### Compile all 9 programs at once

```bash
for f in q*.c; do
    gcc -Wall -Wextra -std=c99 "$f" -o "${f%.c}"
done
```

### Run any binary

```bash
./q1_min_coin
./q2_coin_ways
./q3_lcs
./q4_lis
./q5_msis
./q6_edit_distance
./q7_rod_cutting
./q8_obst
./q9_collatz
```

> **Windows users:** Replace `./q1_min_coin` with `q1_min_coin.exe` and use `gcc` from MinGW or WSL.

---

## Sample Inputs & Outputs

### Q1 — Minimum Coin Change

```text
Enter number of coin denominations: 3
Enter the 3 coin denominations: 1 2 5
Enter target amount V: 11

--- DP Table State (Amount -> Min Coins Needed) ---
Amount:    0    1    2    3    4    5    6    7    8    9   10   11
Coins:     0    1    1    2    2    1    2    2    3    3    2    3
---------------------------------------------------

Coins used to form target amount 11: 1 5 5

Result: Minimum number of coins needed for 11 is: 3
```

---

### Q2 — Coin Change: Total Ways

```text
Enter number of distinct coin denominations: 3
Enter the 3 distinct coin denominations: 1 2 5
Enter target amount V: 5

--- DP Table State (Amount -> Distinct Ways) ---
Amount  0 : 1 ways
Amount  1 : 1 ways
Amount  2 : 2 ways
Amount  3 : 2 ways
Amount  4 : 3 ways
Amount  5 : 4 ways
------------------------------------------------

Total number of distinct combinations to form 5 is: 4
```

Combinations counted: `{5}`, `{2,2,1}`, `{2,1,1,1}`, `{1,1,1,1,1}`

---

### Q3 — Longest Common Subsequence

```text
Enter first sequence (String X): AGGTAB
Enter second sequence (String Y): GXTXAYB

--- 2D DP Table (Dimensions: 7 x 8) ---
        G  X  T  X  A  Y  B
     0  0  0  0  0  0  0  0
  A  0  0  0  0  0  1  1  1
  G  0  1  1  1  1  1  1  1
  G  0  1  1  1  1  1  1  1
  T  0  1  1  2  2  2  2  2
  A  0  1  1  2  2  3  3  3
  B  0  1  1  2  2  3  3  4
-----------------------------------------

Length of Longest Common Subsequence: 4
Reconstructed LCS: "GTAB"
```

---

### Q4 — Longest Increasing Subsequence

```text
Enter number of elements: 8
Enter 8 integers: 10 22 9 33 21 50 41 60

--- DP Table State (Index -> LIS Ending Here) ---
Index:    0    1    2    3    4    5    6    7
Array:   10   22    9   33   21   50   41   60
DP:       1    2    1    3    2    4    3    5
-------------------------------------------------

Length of Longest Increasing Subsequence: 5
Reconstructed LIS: [ 10 22 33 50 60 ]
```

---

### Q5 — Maximum Sum Increasing Subsequence

```text
Enter number of positive integers: 7
Enter 7 positive integers: 1 101 2 3 100 4 5

--- DP Table State (Index -> MSIS Ending Here) ---
Index:    0    1    2    3    4    5    6
Array:    1  101    2    3  100    4    5
MSIS:     1  102    3    6  106    7   12
--------------------------------------------------

Maximum Sum of Increasing Subsequence: 106
Subsequence achieving maximum sum: [ 1 2 3 100 ]
```

---

### Q6 — Edit Distance with Traceback

```text
Enter source string A: kitten
Enter target string B: sitting

--- 2D DP Table (Edit Distance Matrix) ---
        #  s  i  t  t  i  n  g
  #     0  1  2  3  4  5  6  7
  k     1  1  2  3  4  5  6  7
  i     2  2  1  2  3  4  5  6
  t     3  3  2  1  2  3  4  5
  t     4  4  3  2  1  2  3  4
  e     5  5  4  3  2  2  3  4
  n     6  6  5  4  3  3  2  3
------------------------------------------

Minimum Edit Distance (Operations): 3

--- Step-by-Step Transformation (Traceback) ---
Step  1: Keep 'k' → substitute to 's' (or listed as Substitute)
Step  2: Keep 'i' (Match - No operation)
Step  3: Keep 't' (Match - No operation)
Step  4: Keep 't' (Match - No operation)
Step  5: Substitute 'e' with 'i'
Step  6: Keep 'n' (Match - No operation)
Step  7: Insert 'g' into string A
------------------------------------------------
```

---

### Q7 — Rod Cutting with Reconstruction

```text
Enter total length of the rod (n inches): 8
Enter prices for rod lengths from 1 to 8:
  Price for length  1: 1
  Price for length  2: 5
  Price for length  3: 8
  Price for length  4: 9
  Price for length  5: 10
  Price for length  6: 17
  Price for length  7: 17
  Price for length  8: 20

--- DP Table (Rod Length -> Max Revenue & First Cut) ---
Length:       0    1    2    3    4    5    6    7    8
Revenue:      0    1    5    8   10   13   17   18   22
First Cut:    0    1    2    3    2    2    6    1    2
--------------------------------------------------------

(i) Maximum Revenue Obtainable: 22
(ii) Optimal Piece Lengths (Reconstruction): [ 2 6 ]
     Total pieces cut: 2 (Sum of pieces = 8)
```

---

### Q8 — Optimal BST

```text
Enter number of keys (n): 5
Enter probabilities p[1..5]: 0.15 0.10 0.05 0.10 0.20
Enter probabilities q[0..5]: 0.05 0.10 0.05 0.05 0.05 0.10

--- Expected Search Cost Table e[i][j] ---
   j=       0       1       2       3       4       5
i= 1:  0.0500  0.4500  0.9000  1.2500  1.7500  2.7500
i= 2:          0.1000  0.4000  0.7000  1.2000  2.0000
i= 3:                  0.0500  0.2500  0.6000  1.3000
i= 4:                          0.0500  0.3000  1.0000
i= 5:                                  0.0500  0.5000
i= 6:                                          0.1000

--- Optimal Root Table root[i][j] ---
   j=    1    2    3    4    5
i= 1:     1    1    2    2    2
i= 2:          2    2    2    2
i= 3:               3    3    4
i= 4:                    4    5
i= 5:                         5

Minimum Expected Search Cost: 2.7500

--- Optimal Binary Search Tree Structure ---
k2 is the root of the tree
k1 is the left child of k2
d0 is the left child of k1
d1 is the right child of k1
k5 is the right child of k2
k4 is the left child of k5
d3 is the left child of k4
d4 is the right child of k4
d5 is the right child of k5
k3 is the left child of k4 (dummy-level)
--------------------------------------------
```

---

### Q9 — Collatz Conjecture

**Mode 1 — Single value**

```text
Enter your choice (1-3): 1
Enter starting integer n (n >= 1): 27

----------------------------------------------------
   Collatz Analysis for Starting Value n = 27
----------------------------------------------------
Total trajectory points (including start): 112
Total step transitions to reach 1: 111
Peak (maximum value reached in trajectory): 9232

Trajectory Path:
27 -> 82 -> 41 -> 124 -> 62 -> 31 -> 94 -> 47
    -> 142 -> 71 -> 214 -> 107 -> 322 -> 161 -> 484
    ...
    4 -> 2 -> 1
----------------------------------------------------
```

**Mode 2 — Interval**

```text
Enter your choice (1-3): 2
Enter lower bound a: 1
Enter upper bound b: 10

----------------------------------------------------
   Collatz Analysis for Interval [1, 10]
----------------------------------------------------
Number (n)   Steps to 1      Peak Value
----------------------------------------------------
1            0               1
2            1               2
3            7               16
4            2               4
5            5               16
6            8               16
7            16              52
8            3               8
9            19              52
10           6               16
----------------------------------------------------
INTERVAL SUMMARY RESULTS:
  Maximum Trajectory Length (transitions): 19 (achieved by n = 9)
  Highest Peak Value Reached: 52 (achieved by n = 7)
----------------------------------------------------
```


## Credits

**Author:** Vaibhav Maheshwari (B125136) — CSE-B, 3rd Semester  
**Course:** DAA Lab 08 — Dynamic Programming & Recursion  
**Repository:** [github.com/vaibhav-maheshwari22/DAA-LAB](https://github.com/vaibhav-maheshwari22/DAA-LAB)
