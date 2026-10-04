/*
 * Description: Find the median of an array without sorting 
 * using the Quickselect algorithm.
 */

#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b);
int partition(int *arr, int low, int high);
int quickSelect(int *arr, int low, int high, int k);
void get_data(int *arr, int n);

int main() {
    int n;

    printf("Find Median Without Sorting\n");
    printf("---------------------------\n");
    printf("Enter the number of elements (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size!\n");
        return 1;
    }

    // Dynamically allocate memory
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Take manual input from the user
    get_data(arr, n);

    // Median is at index N / 2 (0-based indexing)
    int median_idx = n / 2;
    int median = quickSelect(arr, 0, n - 1, median_idx);

    printf("\nResult: The median of the list is %d.\n", median);

    // Free the allocated memory
    free(arr);
    return 0;
}

// User input function
void get_data(int *arr, int n) {
    printf("\nEnter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
}

// Utility function to swap two integers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Standard Lomuto partition scheme
int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = low;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[high]);
    return i;
}

// Quickselect algorithm
int quickSelect(int *arr, int low, int high, int k) {
    if (low <= high) {
        int pi = partition(arr, low, high);
        
        // If pivot is exactly at the median position
        if (pi == k) return arr[pi];
        
        // If median position is smaller, search the left sub-array
        if (pi > k) return quickSelect(arr, low, pi - 1, k);
        
        // If median position is greater, search the right sub-array
        return quickSelect(arr, pi + 1, high, k);
    }
    return -1;
}