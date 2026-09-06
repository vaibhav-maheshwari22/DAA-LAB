# Question 4: Sorting via Reversal Procedure

## Problem Statement
Suppose you are given a permutation p of the integers 1 to n, and seek to sort them to be in increasing order [1,..., n][cite: 2]. The only operation at your disposal is `reverse(p, i, j)`, which reverses the elements of a subsequence $p_i,...,p_j$ in the permutation[cite: 2]. 
1. **Part 1:** Mathematically, show that it is possible to sort any permutation using $O(n)$ reversals[cite: 2].
2. **Part 2:** Now suppose that the cost of `reverse(p, i, j)` is equal to its length, the number of elements in the range, $|j-i|+1$[cite: 2]. Design an algorithm that sorts p in $O(n \log^2 n)$ cost[cite: 2]. Analyse the running time and cost of your algorithm and prove the correctness[cite: 2].

---

## Part 1: Mathematical Proof for $O(n)$ Reversals
To prove that any permutation of size $n$ can be sorted using at most $O(n)$ reversals, we can construct a deterministic strategy analogous to **Selection Sort**:

1. **Locate the Maximum:** Consider the unsorted prefix of the array $p[1 \dots k]$, where initially $k = n$. Find the position of the maximum element in this prefix. Let its index be $x$ (where $1 \le x \le k$).
2. **First Reversal (Move to Front):** Apply `reverse(p, 1, x)`. This operation flips the sub-array from index 1 to $x$, bringing the maximum element exactly to the first position, $p[1]$.
3. **Second Reversal (Move to Correct Position):** Apply `reverse(p, 1, k)`. This operation flips the entire unsorted prefix, moving the maximum element from $p[1]$ to its correct final position at $p[k]$.
4. **Reduce the Problem:** The maximum element is now correctly placed. Decrement $k$ to $k - 1$ and repeat the process for the remaining elements.

**Conclusion:** For each element placed in its correct sorted position, the algorithm requires at most 2 reversals. To sort all $n$ elements, the total number of reversals required is at most $2n$. Since $2n$ scales linearly with the input size, it is mathematically proven that any permutation can be strictly sorted in **$O(n)$** reversals.

---

## Part 2: Algorithm with $O(n \log^2 n)$ Cost

### Algorithmic Approach
To achieve a minimal execution cost where cost equals the length of the reversed sub-array, the simple $O(n)$ reversal approach fails as its cost would be $O(n^2)$. We solve this using an **In-Place Merge Sort** algorithm:
1. Divide the array into two halves recursively until the base case of size 1.
2. To merge two adjacent sorted blocks $A$ and $B$, we find the median element in $A$ using binary search in $B$ to determine the exact split points.
3. We use the **Block Swap Algorithm (Rotation)** to exchange the right half of $A$ and the left half of $B$. Rotating two blocks takes exactly 3 reversals and its cost is strictly bounded linearly by the sum of their lengths.
4. We recursively merge the remaining fragmented blocks.

### Complexity Analysis
* **Merging Cost:** The binary search and block rotations partition the blocks. The recurrence for the merge step is $Cost_{merge}(N) = 2 \cdot Cost_{merge}(N/2) + O(N)$, which resolves mathematically to $O(N \log N)$.
* **Total Sorting Cost & Running Time:** The overall Merge Sort recurrence becomes $T(N) = 2T(N/2) + Cost_{merge}(N)$. Substituting the merge cost yields $T(N) = 2T(N/2) + O(N \log N)$. According to the Master Theorem, this resolves strictly to an **$O(N \log^2 N)$** worst-case running time and cost.
* **Space Complexity:** $O(1)$ auxiliary space (excluding the $O(\log n)$ recursive stack) because all block rotations and reversals operate entirely in-place.