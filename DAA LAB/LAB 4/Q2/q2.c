/*
 * Description:  algorithm to find if there exists a pair 
 * that adds up to a given number x.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void get_data(int *arr, int n, char *name);
int compare_ints(const void *a, const void *b);
bool binary_search(int *arr, int n, int target);
bool find_pair(int *S1, int *S2, int n, int x, int *res1, int *res2);

int main() {
    int n, x;

    printf("Two Set Target Sum\n");
    printf("------------------\n");
    printf("Enter the size of the sets (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size!\n");
        return 1;
    }

    printf("Enter the target sum (x): ");
    scanf("%d", &x);

    // Dynamically allocate memory
    int *S1 = (int *)malloc(n * sizeof(int));
    int *S2 = (int *)malloc(n * sizeof(int));

    if (S1 == NULL || S2 == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Take input from the user
    get_data(S1, n, "S1");
    get_data(S2, n, "S2");

    int res1 = 0, res2 = 0;

    // Perform search
    if (find_pair(S1, S2, n, x, &res1, &res2)) {
        printf("\nResult: Pair found! (%d from S1) + (%d from S2) = %d\n", res1, res2, x);
    } else {
        printf("\nResult: No such pair exists that adds up to %d.\n", x);
    }

    // Free the allocated memory
    free(S1);
    free(S2);
    return 0;
}

// User input function for sets
void get_data(int *arr, int n, char *name) {
    printf("\nEnter %d elements for Set %s:\n", n, name);
    for (int i = 0; i < n; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
}

// Comparator function for qsort
int compare_ints(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// binary search logic
bool binary_search(int *arr, int n, int target) {
    int left = 0, right = n - 1;
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

// to find the pair across both sets
bool find_pair(int *S1, int *S2, int n, int x, int *res1, int *res2) {
    // Sort S2
    qsort(S2, n, sizeof(int), compare_ints);

    // Iterate through S1 and binary search in S2 
    for (int i = 0; i < n; i++) {
        int required = x - S1[i];
        
        if (binary_search(S2, n, required)) {
            *res1 = S1[i];
            *res2 = required;
            return true;
        }
    }
    return false;
}