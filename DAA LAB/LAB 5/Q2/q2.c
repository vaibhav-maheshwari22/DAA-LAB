/*
 * Description: Find the K'th smallest element in an array 
 * without sorting using the Quickselect algorithm.
 */

#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b);
int partition(int *arr, int low, int high);
int quickSelect(int *arr, int low, int high, int k);
void get_data(int *arr, int n);

int main() {
    int n, k;

    printf("Find K'th Smallest Element\n");
    printf("--------------------------\n");
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

    printf("Enter the value of K (1 to %d): ", n);
    scanf("%d", &k);

    if (k < 1 || k > n) {
        printf("Invalid K! It must be between 1 and %d.\n", n);
        free(arr);
        return 1;
    }

    // K'th smallest element is at index K-1
    int kth_smallest = quickSelect(arr, 0, n - 1, k - 1);

    printf("\nResult: The %d'th smallest element is %d.\n", k, kth_smallest);

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
int quickSelect(int *arr, int low, int high, int target_index) {
    if (low <= high) {
        int pi = partition(arr, low, high);
        
        // If pivot is exactly at the K'th position
        if (pi == target_index) return arr[pi];
        
        // If target position is smaller, search the left sub-array
        if (pi > target_index) return quickSelect(arr, low, pi - 1, target_index);
        
        // If target position is greater, search the right sub-array
        return quickSelect(arr, pi + 1, high, target_index);
    }
    return -1;
}