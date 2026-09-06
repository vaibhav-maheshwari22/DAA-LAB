# Question 1: 1D Array Operations and Complexities

## Problem Statement
Given an array with $n$ unsorted integer elements, determine the worst-case complexity of 9 specific operations in terms of $n$, and write a C program to validate the procedures[cite: 2]. 

## Algorithmic Approach & Complexity Analysis
Since the input array is unsorted, many operations require a full linear scan or a sorting step first.

* **(i) Finding the maximum element:** 
  * **Complexity:** $O(n)$
  * **Reason:** Requires a single linear scan through the array to track the highest value.
* **(ii) Finding the first and second largest elements:** 
  * **Complexity:** $O(n)$
  * **Reason:** Requires a single linear scan while maintaining two separate variables for the top two maximums.
* **(iii) Finding the mean:** 
  * **Complexity:** $O(n)$
  * **Reason:** Requires traversing all $n$ elements once to compute their sum.
* **(iv) Finding the median:** 
  * **Complexity:** $O(n^2)$ worst-case ($O(n)$ average)
  * **Reason:** Utilizing the QuickSelect partition algorithm. The worst-case occurs if the array is already sorted and the pivot choice is extremely unbalanced.
* **(v) Finding the standard deviation:** 
  * **Complexity:** $O(n)$
  * **Reason:** Requires two linear passes: one to calculate the mean, and another to calculate the sum of squared differences from the mean.
* **(vi) Finding the mode:** 
  * **Complexity:** $O(n \log n)$
  * **Reason:** To accurately count frequencies without a hash map (which requires $O(n)$ space), the array is sorted first using Quick Sort $O(n \log n)$, followed by a single linear scan $O(n)$ to find the longest contiguous frequency.
* **(vii) Removing all duplicates:** 
  * **Complexity:** $O(n \log n)$
  * **Reason:** The array is first sorted in $O(n \log n)$ time. Then, a two-pointer approach compresses the unique elements in-place in strictly $O(n)$ time.
* **(viii) Reversing the elements of the array:** 
  * **Complexity:** $O(n)$
  * **Reason:** Swapping elements from the outermost indices moving inward takes exactly $n/2$ operations.
* **(ix) Partitioning the array with respect to a random pivot:** 
  * **Complexity:** $O(n)$
  * **Reason:** Modified Lomuto partition requires a single pass where elements $\ge$ pivot are placed on the left, and elements $<$ pivot are placed on the right.