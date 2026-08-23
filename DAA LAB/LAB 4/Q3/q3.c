/*
 * Description: algorithm to test whether 
 * k integers in a set S add up to a target T.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void get_data(int *arr, int n);
int compare_ints(const void *a, const void *b);
bool binary_search(int *arr, int start, int n, int target);
bool find_k_sum(int *S, int start, int n, int k, int target, int *res, int res_idx);

int main() {
    int n, k, T;

    printf("K-Sum Target Search\n");
    printf("-------------------\n");
    printf("Enter the size of the set (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size!\n");
        return 1;
    }

    printf("Enter the value of k: ");
    scanf("%d", &k);

    if (k <= 0 || k > n) {
        printf("Invalid k! It must be between 1 and n.\n");
        return 1;
    }

    printf("Enter the target sum (T): ");
    scanf("%d", &T);

    // Dynamically allocate memory
    int *S = (int *)malloc(n * sizeof(int));
    int *res = (int *)malloc(k * sizeof(int)); // To store the successful combination

    if (S == NULL || res == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Take input from the user
    get_data(S, n);

    // Sort the array
    qsort(S, n, sizeof(int), compare_ints);

    // Perform recursive search
    if (find_k_sum(S, 0, n, k, T, res, 0)) {
        printf("\nResult: Elements found that sum to %d:\n", T);
        for (int i = 0; i < k; i++) {
            printf("%d ", res[i]);
            if (i < k - 1) printf("+ ");
        }
        printf("= %d\n", T);
    } else {
        printf("\nResult: No %d elements add up to %d.\n", k, T);
    }

    // Free the allocated memory
    free(S);
    free(res);
    return 0;
}

// User input function
void get_data(int *arr, int n) {
    printf("\nEnter %d elements for the set:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
}

// Comparator function for qsort
int compare_ints(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Binary search logic targeting a specific range [start, n-1]
bool binary_search(int *arr, int start, int n, int target) {
    int left = start, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return true;
        }
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return false;
}

// Recursive logic to fix (k-1) elements and binary search the last one
bool find_k_sum(int *S, int start, int n, int k, int target, int *res, int res_idx) {
    // Base case: if k == 1, perform binary search in the remaining elements
    if (k == 1) {
        if (binary_search(S, start, n, target)) {
            res[res_idx] = target;
            return true;
        }
        return false;
    }

    // Recursive step: Fix one element, and find (k-1)-sum in the rest 
    for (int i = start; i <= n - k; i++) {
        res[res_idx] = S[i];
        
        // Skip duplicate elements
        if (i > start && S[i] == S[i-1]) continue;

        if (find_k_sum(S, i + 1, n, k - 1, target - S[i], res, res_idx + 1)) {
            return true;
        }
    }
    return false;
}