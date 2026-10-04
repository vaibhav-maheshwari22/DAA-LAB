#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Merge Two Sorted Arrays

// Standard merge logic to combine two arrays into a newly allocated block.
// Time Complexity: O(size1 + size2)
int* merge_two_arrays(int *arr1, int size1, int *arr2, int size2) {
    int *merged = (int *)malloc((size1 + size2) * sizeof(int));
    int i = 0, j = 0, k = 0;
    
    // Compare and place smaller elements first
    while (i < size1 && j < size2) {
        if (arr1[i] <= arr2[j]) {
            merged[k++] = arr1[i++];
        } else {
            merged[k++] = arr2[j++];
        }
    }
    
    // Flush remaining elements
    while (i < size1) merged[k++] = arr1[i++];
    while (j < size2) merged[k++] = arr2[j++];
    
    return merged;
}


// METHOD 1: Sequential Merge

// Merges K arrays one by one in a linear fashion.
// Time Complexity: O(n * k^2)
int* merge_sequential(int **arr, int k, int n, int *out_size) {
    if (k == 0 || arr == NULL) {
        *out_size = 0;
        return NULL;
    }
    
    int current_size = n;
    int *result = (int *)malloc(current_size * sizeof(int));
    
    // Initialize with the first array
    for (int i = 0; i < current_size; i++) {
        result[i] = arr[0][i];
    }
    
    // Sequentially merge the remaining (K - 1) arrays
    for (int i = 1; i < k; i++) {
        int *temp = merge_two_arrays(result, current_size, arr[i], n);
        free(result); // Prevent memory leaks
        result = temp;
        current_size += n;
    }
    
    *out_size = current_size;
    return result;
}


// METHOD 2: Divide and Conquer Merge

// Recursively halves the array list to merge in a tree-like structure.
// Time Complexity: O(n * k * log_2 k)
int* merge_divide_conquer(int **arr, int n, int left, int right, int *out_size) {
    // Base Case: Single array reached
    if (left == right) {
        *out_size = n;
        int *copy = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) copy[i] = arr[left][i];
        return copy;
    }
    
    if (left < right) {
        int mid = left + (right - left) / 2;
        int left_size = 0, right_size = 0;
        
        // Recursively divide
        int *left_merged = merge_divide_conquer(arr, n, left, mid, &left_size);
        int *right_merged = merge_divide_conquer(arr, n, mid + 1, right, &right_size);
        
        // Merge the bounded halves
        int *final_merged = merge_two_arrays(left_merged, left_size, right_merged, right_size);
        *out_size = left_size + right_size;
        
        free(left_merged);
        free(right_merged);
        
        return final_merged;
    }
    
    *out_size = 0;
    return NULL;
}


int main() {
    srand(time(NULL));
    
    // Testing specific K values. N is fixed to 1000 elements per array.
    int k_vals[] = {50, 100, 200, 300, 400, 500};
    int num_tests = sizeof(k_vals) / sizeof(k_vals[0]);
    int n = 1000;
    
    FILE *file = fopen("q3_benchmark.csv", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    fprintf(file, "K,N,Time_Sequential,Time_DivideConquer\n");
    printf("Benchmarking K-Sorted Arrays Merge (N = %d fixed)...\n\n", n);

    for (int t = 0; t < num_tests; t++) {
        int k = k_vals[t];
        
        // Generate K sorted arrays natively in O(N) to save setup time
        int **lists = (int **)malloc(k * sizeof(int *));
        for (int i = 0; i < k; i++) {
            lists[i] = (int *)malloc(n * sizeof(int));
            lists[i][0] = rand() % 100;
            for (int j = 1; j < n; j++) {
                lists[i][j] = lists[i][j - 1] + (rand() % 10); 
            }
        }
        
        clock_t start, end;
        
        // Method 1: Sequential
        int final_size1 = 0;
        start = clock();
        int *res_seq = merge_sequential(lists, k, n, &final_size1);
        end = clock();
        double time_seq = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        // Method 2: Divide & Conquer
        int final_size2 = 0;
        start = clock();
        int *res_dc = merge_divide_conquer(lists, n, 0, k - 1, &final_size2);
        end = clock();
        double time_dc = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        fprintf(file, "%d,%d,%f,%f\n", k, n, time_seq, time_dc);
        printf("K = %-4d | Sequential Time: %-7.4f s | Divide & Conquer Time: %-7.4f s\n", k, time_seq, time_dc);
        
        // Safely free allocated memory
        free(res_seq);
        free(res_dc);
        for (int i = 0; i < k; i++) free(lists[i]);
        free(lists);
    }
    
    fclose(file);
    printf("\nBenchmark complete! Results saved '\n");
    return 0;
}