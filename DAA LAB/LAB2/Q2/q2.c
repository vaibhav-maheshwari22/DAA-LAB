#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// 1. STANDARD 2-WAY MERGE SORT


// Standard subroutine to merge two sorted halves
void merge_2way(int *arr, int low, int mid, int high) {
    int len1 = mid - low + 1;
    int len2 = high - mid;
    
    int *left_arr = (int *)malloc(len1 * sizeof(int));
    int *right_arr = (int *)malloc(len2 * sizeof(int));
    
    for (int i = 0; i < len1; i++) left_arr[i] = arr[low + i];
    for (int i = 0; i < len2; i++) right_arr[i] = arr[mid + 1 + i];
    
    int i = 0, j = 0, k = low;
    while (i < len1 && j < len2) {
        if (left_arr[i] <= right_arr[j]) arr[k++] = left_arr[i++];
        else arr[k++] = right_arr[j++];
    }
    
    while (i < len1) arr[k++] = left_arr[i++];
    while (j < len2) arr[k++] = right_arr[j++];
    
    free(left_arr);
    free(right_arr);
}

// Standard O(n log_2 n) Merge Sort
void merge_sort_standard(int *arr, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        merge_sort_standard(arr, low, mid);
        merge_sort_standard(arr, mid + 1, high);
        merge_2way(arr, low, mid, high);
    }
}


// 2. MODIFIED 3-WAY MERGE SORT


// Dedicated subroutine to simultaneously merge three sorted arrays
void merge_3way(int *arr, int low, int mid1, int mid2, int high) {
    int len1 = mid1 - low + 1;
    int len2 = mid2 - mid1;
    int len3 = high - mid2;

    int *L = (int *)malloc(len1 * sizeof(int));
    int *M = (int *)malloc(len2 * sizeof(int));
    int *R = (int *)malloc(len3 * sizeof(int));

    for (int i = 0; i < len1; i++) L[i] = arr[low + i];
    for (int i = 0; i < len2; i++) M[i] = arr[mid1 + 1 + i];
    for (int i = 0; i < len3; i++) R[i] = arr[mid2 + 1 + i];

    int i = 0, j = 0, k = 0, dest = low;

    // Compare across all three arrays
    while (i < len1 && j < len2 && k < len3) {
        if (L[i] <= M[j]) {
            if (L[i] <= R[k]) arr[dest++] = L[i++];
            else arr[dest++] = R[k++];
        } else {
            if (M[j] <= R[k]) arr[dest++] = M[j++];
            else arr[dest++] = R[k++];
        }
    }

    // Compare across remaining two arrays
    while (i < len1 && j < len2) {
        if (L[i] <= M[j]) arr[dest++] = L[i++];
        else arr[dest++] = M[j++];
    }
    while (j < len2 && k < len3) {
        if (M[j] <= R[k]) arr[dest++] = M[j++];
        else arr[dest++] = R[k++];
    }
    while (i < len1 && k < len3) {
        if (L[i] <= R[k]) arr[dest++] = L[i++];
        else arr[dest++] = R[k++];
    }

    // Flush any single remaining array
    while (i < len1) arr[dest++] = L[i++];
    while (j < len2) arr[dest++] = M[j++];
    while (k < len3) arr[dest++] = R[k++];

    free(L); free(M); free(R);
}

// Modified O(n log_3 n) Merge Sort
void merge_sort_modified(int *arr, int low, int high) {
    if (low >= high) return;
    
    // Base case for exactly 2 elements
    if (high - low == 1) { 
        if (arr[low] > arr[high]) {
            int temp = arr[low];
            arr[low] = arr[high];
            arr[high] = temp;
        }
        return;
    }
    
    // Divide array into roughly 3 equal thirds
    int third = (high - low) / 3;
    int mid1 = low + third;
    int mid2 = low + 2 * third + 1;
    
    // Recursively sort the 3 parts
    merge_sort_modified(arr, low, mid1);
    merge_sort_modified(arr, mid1 + 1, mid2);
    merge_sort_modified(arr, mid2 + 1, high);
    
    // Combine using the specific 3-way merge subroutine
    merge_3way(arr, low, mid1, mid2, high);
}


// 3. BENCHMARKING FRAMEWORK


int main() {
    srand(time(NULL));
    
    // Using scaled array sizes for proper time observation
    int sizes[] = {10000, 20000, 40000, 80000, 100000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    FILE *file = fopen("q2_merge_comparison.csv", "w");
    if (file == NULL) {
        printf("Error: Could not create output file!\n");
        return 1;
    }
    
    fprintf(file, "Size,Time_2Way,Time_3Way\n");
    printf("Initiating Performance Benchmark...\n\n");
    
    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        int *arr_standard = (int *)malloc(n * sizeof(int));
        int *arr_modified = (int *)malloc(n * sizeof(int));
        

        for (int i = 0; i < n; i++) {
            int random_val = rand() % 500000;
            arr_standard[i] = random_val;
            arr_modified[i] = random_val; 
        }
        
        clock_t start, end;
        double time_2way, time_3way;
        
        // Standard 2-Way Merge Sort 
        start = clock();
        merge_sort_standard(arr_standard, 0, n - 1);
        end = clock();
        time_2way = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        // Modified 3-Way Merge Sort
        start = clock();
        merge_sort_modified(arr_modified, 0, n - 1);
        end = clock();
        time_3way = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        fprintf(file, "%d,%f,%f\n", n, time_2way, time_3way);
        printf("Array Size: %-7d | 2-Way Time: %f s | 3-Way Time: %f s\n", n, time_2way, time_3way);
        
        free(arr_standard);
        free(arr_modified);
    }
    
    fclose(file);
    printf("\nExecution complete. Data successfully saved to 'q2_merge_comparison.csv'.\n");
    return 0;
}