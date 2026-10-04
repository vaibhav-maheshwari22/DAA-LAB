#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZES 7
#define PROBES 100

typedef struct {
    int min;
    int max;
} MinMax;

int n_vals[SIZES] = {2, 8, 32, 128, 512, 2048, 8192};
long long avg_dc[SIZES], avg_naive[SIZES];

MinMax find_min_max(int *arr, int low, int high, long long *comps);
MinMax naive_min_max(int *arr, int n, long long *comps);
void run_test(int idx);

int main() {
    srand(time(0));
    
    printf("Evaluating Max-Min D&C Algorithm...\n\n");
    printf("%-8s | %-12s | %-12s | %-15s\n", "N", "D&C Comps", "Naive Comps", "Theoretical (3N/2 - 2)");
    printf("------------------------------------------------------------------\n");
    
    for (int i = 0; i < SIZES; i++) {
        run_test(i);
        long long bound = (3 * n_vals[i] / 2) - 2;
        
        printf("%-8d | %-12lld | %-12lld | %-15lld\n", 
               n_vals[i], avg_dc[i], avg_naive[i], bound);
    }

    // Export to CSV
    FILE *fp = fopen("q3_data.csv", "w");
    if (fp) {
        fprintf(fp, "N,DC_Comps,Naive_Comps,Theoretical\n");
        for (int i = 0; i < SIZES; i++) {
            long long bound = (3 * n_vals[i] / 2) - 2;
            fprintf(fp, "%d,%lld,%lld,%lld\n", n_vals[i], avg_dc[i], avg_naive[i], bound);
        }
        fclose(fp);
    }
    
    return 0;
}

// Recursive Divide & Conquer function
MinMax find_min_max(int *arr, int low, int high, long long *comps) {
    MinMax result, left, right;
    
    // Base Case 1: Only one element
    if (low == high) {
        result.min = arr[low];
        result.max = arr[low];
        return result;
    }
    
    // Base Case 2: Exactly two elements
    if (high == low + 1) {
        (*comps)++;
        if (arr[low] > arr[high]) {
            result.max = arr[low];
            result.min = arr[high];
        } else {
            result.max = arr[high];
            result.min = arr[low];
        }
        return result;
    }
    
    // Divide
    int mid = low + (high - low) / 2;
    left = find_min_max(arr, low, mid, comps);
    right = find_min_max(arr, mid + 1, high, comps);
    
    // Conquer
    (*comps)++;
    result.min = (left.min < right.min) ? left.min : right.min;
    
    (*comps)++;
    result.max = (left.max > right.max) ? left.max : right.max;
    
    return result;
}

// Obvious linear scan for cross-validation
MinMax naive_min_max(int *arr, int n, long long *comps) {
    MinMax res;
    res.min = arr[0];
    res.max = arr[0];
    
    for (int i = 1; i < n; i++) {
        (*comps)++; 
        if (arr[i] < res.min) {
            res.min = arr[i];
        } else {
            // Only check max if it wasn't a new min
            (*comps)++; 
            if (arr[i] > res.max) res.max = arr[i];
        }
    }
    return res;
}

// Testing and Validation Logic
void run_test(int idx) {
    int n = n_vals[idx];
    long long sum_dc = 0, sum_naive = 0;
    
    int *arr = (int *)malloc(n * sizeof(int));
    
    for (int p = 0; p < PROBES; p++) {
        for (int i = 0; i < n; i++) arr[i] = rand() % 100000;
        
        long long c_dc = 0, c_naive = 0;
        MinMax res_dc = find_min_max(arr, 0, n - 1, &c_dc);
        MinMax res_naive = naive_min_max(arr, n, &c_naive);
        
        if (res_dc.min != res_naive.min || res_dc.max != res_naive.max) {
            printf("Mismatch Error at N=%d!\n", n);
            exit(1);
        }
        
        sum_dc += c_dc;
        sum_naive += c_naive;
    }
    
    avg_dc[idx] = sum_dc / PROBES;
    avg_naive[idx] = sum_naive / PROBES;
    
    free(arr);
}