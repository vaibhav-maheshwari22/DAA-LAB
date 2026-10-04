# Q5: Find the Partition Point

## Objective
To implement a method that finds the exact point of transition in an array of size 'n' containing a run of 0's followed by a run of 1's.

## Approach & Implementation Logic
The array strictly consists of 0's followed by 1's, meaning the data is fundamentally sorted in non-decreasing order. Rather than using a linear search which would yield a time complexity of O(n), I implemented a **Binary Search** algorithm to optimize the process. For testing and demonstration purposes, I have used a custom, hardcoded array directly within the code.

1. **Binary Search Logic:** The algorithm calculates the middle index (`mid`).
2. If the element at `mid` is `0`, the transition point must exist in the right half of the array, so the search space is updated to `low = mid + 1`.
3. If the element at `mid` is `1`, it could either be the first `1` or a subsequent `1`. The algorithm checks the preceding element (`mid - 1`). If the preceding element is `0` (or if `mid` is the 0th index), the exact transition point has been found. Otherwise, the search space is shifted to the left half using `high = mid - 1`.

## Conclusion
By utilizing the binary search method, the time complexity is significantly reduced to **O(log n)**. This is highly efficient and optimally scales for extremely large values of 'n' compared to a sequential scan.

## Input & Output
*   **Input:** A custom, hardcoded array `arr[] = {0, 0, 0, 0, 1, 1, 1, 1}` defined in the main function, along with its calculated size `n`.
*   **Output:** The terminal prints the exact index where the first '1' occurs (Index: 4).