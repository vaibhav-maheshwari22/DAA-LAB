/*
 DAA Lab 08 - Q5: Maximum Sum Increasing Subsequence (MSIS)

 Input:
   - n = size of array
   - n positive integers

 Output:
   Maximum possible sum of a strictly increasing subsequence,
   and the actual subsequence that gives that sum.

 Time Complexity: O(n^2)
   For each i, we check all j < i. Total comparisons ~ n^2/2.
   Finding max and reconstructing takes O(n).

 Space Complexity: O(n)
   msis[] and parent[] arrays of size n.
*/

#include <stdio.h>
#include <stdlib.h>

void computeMSIS(int A[], int n) {
    if (n <= 0) return;

    // msis[i] = max sum of increasing subseq ending at i
    int *msis = (int *)malloc(n * sizeof(int));

    // parent[i] = previous index in the optimal subseq ending at i
    int *parent = (int *)malloc(n * sizeof(int));

    if (msis == NULL || parent == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    // Base: every element alone is an increasing subseq
    for (int i = 0; i < n; i++) {
        msis[i] = A[i];
        parent[i] = -1;
    }

    // Build msis table
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            // Strictly increasing: A[j] < A[i]
            // msis[i] = max(msis[i], msis[j] + A[i])
            if (A[j] < A[i] && msis[j] + A[i] > msis[i]) {
                msis[i] = msis[j] + A[i];
                parent[i] = j;
            }
        }
    }

    // Find max sum and its ending index
    int max_sum = msis[0];
    int max_index = 0;

    for (int i = 1; i < n; i++) {
        if (msis[i] > max_sum) {
            max_sum = msis[i];
            max_index = i;
        }
    }

    // Print DP state
    printf("\n--- DP Table State (Index -> MSIS Ending Here) ---\n");
    printf("Index: ");
    for (int i = 0; i < n; i++) printf("%4d ", i);
    printf("\nArray: ");
    for (int i = 0; i < n; i++) printf("%4d ", A[i]);
    printf("\nMSIS:  ");
    for (int i = 0; i < n; i++) printf("%4d ", msis[i]);
    printf("\n--------------------------------------------------\n");

    printf("\nMaximum Sum of Increasing Subsequence: %d\n", max_sum);

    // Reconstruct subsequence using parent array
    int *seq = (int *)malloc(n * sizeof(int));
    int count = 0;
    int curr = max_index;

    while (curr != -1) {
        seq[count++] = A[curr];
        curr = parent[curr];
    }

    printf("Subsequence achieving maximum sum: [ ");
    for (int i = count - 1; i >= 0; i--) {
        printf("%d ", seq[i]);
    }
    printf("]\n");

    free(seq);
    free(msis);
    free(parent);
}

int main() {
    int n;

    printf("====================================================\n");
    printf("     Maximum Sum Increasing Subsequence (MSIS)      \n");
    printf("====================================================\n");

    printf("Enter number of positive integers: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid array size.\n");
        return 1;
    }

    int *A = (int *)malloc(n * sizeof(int));
    if (A == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter %d positive integers: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    computeMSIS(A, n);

    free(A);
    return 0;
}