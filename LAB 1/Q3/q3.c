#include <stdio.h>
#include <stdlib.h>

// (i) Optimized Bubble Sort
long bubble_sort_optimized(int arr[], int n) {

    long comparisons = 0;
    int swapped;

    for (int i = 0; i < n - 1; i++) {

        swapped = 0;

        for (int j = 0; j < n - i - 1; j++) {

            comparisons++;

            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }

        // Early exit
        if (swapped == 0) break;
    }

    return comparisons;
}

// (ii) Strict Bubble Sort
long bubble_sort_strict(int arr[], int n) {

    long comparisons = 0;

    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - 1; j++) {

            comparisons++;

            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    return comparisons;
}

int main() {

    FILE *fp = fopen("q3_data.csv", "w");

    if (fp == NULL) return 1;

    fprintf(fp, "n,optimized_comparisons,strict_comparisons\n");

    int sizes[] = {10, 50, 100, 200, 300, 500, 800, 1000};
    int num_tests = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < num_tests; i++) {

        int n = sizes[i];

        // Dynamically allocate memory
        int *arr1 = (int *)malloc(n * sizeof(int));
        int *arr2 = (int *)malloc(n * sizeof(int));

        // Fill arrays with identical randomized data
        for (int j = 0; j < n; j++) {
            int val = rand() % 10000;
            arr1[j] = val;
            arr2[j] = val;
        }

        long opt_comp = bubble_sort_optimized(arr1, n);
        long strict_comp = bubble_sort_strict(arr2, n);
        
        fprintf(fp, "%d,%ld,%ld\n", n, opt_comp, strict_comp);
        
        free(arr1);
        free(arr2);
    }
    
    fclose(fp);
    printf("Data successfully written to q3_data.csv\n");

    return 0;
}
