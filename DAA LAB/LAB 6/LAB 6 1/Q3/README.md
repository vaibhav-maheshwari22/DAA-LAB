# Question 3: Vector Convolution in $O(n \log n)$ Time

## Problem Statement
The convolution of two vectors A and B is a new vector C such that $C[k] = \sum_{j=0}^{m-1} A[j]B[k-j]$[cite: 2]. Find an $O(n \log n)$ divide and conquer algorithm for this operation, assuming lengths are $m$ and $n$[cite: 2].

## Algorithmic Approach (Divide & Conquer)
A standard nested-loop convolution requires $O(n \cdot m)$ operations. To strictly meet the $O(n \log n)$ constraint, this implementation leverages the **Fast Fourier Transform (FFT)** theorem: Convolution in the time domain is equivalent to point-wise multiplication in the frequency domain.

1. **Zero-Padding:** The target size of the convolution is $m + n - 1$. For the Radix-2 FFT algorithm to work, we pad both input vectors with zeros until their length $N$ reaches the next closest power of 2.
2. **Forward FFT (Divide & Conquer):** We recursively split the polynomials into even and odd degree terms, computing the FFT of vectors $A$ and $B$ in $O(N \log N)$ time.
3. **Point-wise Multiplication:** We compute $C_{freq}[i] = A_{freq}[i] \times B_{freq}[i]$ strictly in $O(N)$ time.
4. **Inverse FFT:** Finally, we run the inverse FFT on $C_{freq}$ to map the polynomial back to the standard time domain, recovering the convolved vector in $O(N \log N)$ time.

## Complexity Analysis
* **Time Complexity:** 
  * Forward transforms: $2 \times O(N \log N)$
  * Point-wise multiplication: $O(N)$
  * Inverse transform: $O(N \log N)$
  * **Overall Time Complexity:** strictly $O(N \log N)$, solving the bottleneck.
* **Space Complexity:** $O(N)$ auxiliary space required for generating and storing the `double complex` arrays during the FFT merges.