/*
 DAA Lab 08 - Q4: Longest Increasing Subsequence (strictly increasing)

 Input:
   - n = size of array
   - n integers

 Time Complexity: O(n^2)
   Nested loops: for each i, check all j < i.

 Space Complexity: O(n)
   dp[] and parent[] arrays.
*/

#include <stdio.h>
#include <stdlib.h>

void computeLIS(int A[], int n) {
    if (n <= 0) return;

    int i, j;

    // dp[i] = length of LIS ending at index i
    int *dp = (int *)malloc(n * sizeof(int));

    // parent[i] = previous index in the LIS ending at i
    int *parent = (int *)malloc(n * sizeof(int));

    if (dp == NULL || parent == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    // Base: every element alone is an increasing subseq of length 1
    for (i = 0; i < n; i++) {
        dp[i] = 1;
        parent[i] = -1;
    }

    // Build dp table
    for (i = 1; i < n; i++) {
        for (j = 0; j < i; j++) {
            // Strictly increasing
            if (A[j] < A[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
    }

    // Find max length and its ending index
    int maxLen = dp[0];
    int maxIdx = 0;
    for (i = 1; i < n; i++) {
        if (dp[i] > maxLen) {
            maxLen = dp[i];
            maxIdx = i;
        }
    }

    // Print DP table
    printf("\n--- DP Table State (Index -> LIS Ending Here) ---\n");
    printf("Index: ");
    for (i = 0; i < n; i++) printf("%4d ", i);
    printf("\nArray: ");
    for (i = 0; i < n; i++) printf("%4d ", A[i]);
    printf("\nDP:    ");
    for (i = 0; i < n; i++) printf("%4d ", dp[i]);
    printf("\n-------------------------------------------------\n");

    printf("\nLength of Longest Increasing Subsequence: %d\n", maxLen);

    // Reconstruct LIS
    int *seq = (int *)malloc(maxLen * sizeof(int));
    int cur = maxIdx;
    int k = maxLen - 1;
    while (cur != -1) {
        seq[k--] = A[cur];
        cur = parent[cur];
    }

    printf("Reconstructed LIS: [ ");
    for (i = 0; i < maxLen; i++) printf("%d ", seq[i]);
    printf("]\n");

    free(seq);
    free(dp);
    free(parent);
}

int main() {
    int n, i;

    printf("====================================================\n");
    printf("      Longest Increasing Subsequence (LIS)          \n");
    printf("====================================================\n");

    printf("Enter number of elements in the array: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid array size.\n");
        return 1;
    }

    int *A = (int *)malloc(n * sizeof(int));
    if (A == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter %d integers: ", n);
    for (i = 0; i < n; i++) scanf("%d", &A[i]);

    computeLIS(A, n);

    free(A);
    return 0;
}