/*
 * Description: Quick sort of N random elements stored in a file.
 * Includes automated validation to verify the sorting order.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void swap(int *a, int *b);
int partition(int *arr, int low, int high);
void quickSort(int *arr, int low, int high);
bool validate_sort(int *arr, int n);

int main() {
    int n;
    const char *infile = "input_qs.txt";
    const char *outfile = "output_qs.txt";

    printf("Quick Sort (Randomized File I/O)\n");
    printf("--------------------------------\n");
    printf("Enter the number of random elements to generate (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size!\n");
        return 1;
    }

    // 1. Generate random elements and write to input file
    FILE *fp_in = fopen(infile, "w");
    if (fp_in == NULL) {
        printf("Error creating input file!\n");
        return 1;
    }
    srand(time(NULL)); // Seed for randomness
    for (int i = 0; i < n; i++) {
        fprintf(fp_in, "%d ", rand() % 10000); // Random numbers between 0 and 9999
    }
    fclose(fp_in);
    printf("[+] Generated %d random elements and saved to '%s'.\n", n, infile);

    // 2. Read elements from input file into an array
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    fp_in = fopen(infile, "r");
    for (int i = 0; i < n; i++) {
        fscanf(fp_in, "%d", &arr[i]);
    }
    fclose(fp_in);
    printf("[+] Read %d elements from '%s' into memory.\n", n, infile);

    // 3. Apply Quick Sort
    quickSort(arr, 0, n - 1);
    printf("[+] Applied Quick Sort.\n");

    // 4. Validate the sorting
    if (validate_sort(arr, n)) {
        printf("[+] VALIDATION SUCCESS: The array is correctly sorted!\n");
    } else {
        printf("[-] VALIDATION FAILED: The array is not sorted properly.\n");
    }

    // 5. Write the sorted elements to output file
    FILE *fp_out = fopen(outfile, "w");
    if (fp_out == NULL) {
        printf("Error opening output file!\n");
        free(arr);
        return 1;
    }
    for (int i = 0; i < n; i++) {
        fprintf(fp_out, "%d ", arr[i]);
    }
    fclose(fp_out);
    printf("[+] Sorted elements saved to '%s'.\n", outfile);

    free(arr);
    return 0;
}

// Utility function to swap two integers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Validation function
bool validate_sort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

// Standard Lomuto partition scheme for Quick Sort
int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Quick Sort algorithm
void quickSort(int *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}