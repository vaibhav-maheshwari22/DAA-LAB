/*
 * Description: Implement Heap Sort to sort N randomly generated 
 * elements stored in a file, including complexity validation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void swap(int *a, int *b);
void heapify(int *arr, int n, int i);
void heapSort(int *arr, int n);
bool validate_sort(int *arr, int n);

int main() {
    int n;
    const char *infile = "input_hs.txt";
    const char *outfile = "output_hs.txt";

    printf("Heap Sort (Randomized File I/O)\n");
    printf("-------------------------------\n");
    printf("Enter the number of random elements to generate (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size!\n");
        return 1;
    }

    // 1. Generate random elements and write to file
    FILE *fp_in = fopen(infile, "w");
    if (fp_in == NULL) {
        printf("Error creating input file!\n");
        return 1;
    }
    srand(time(NULL)); 
    for (int i = 0; i < n; i++) {
        fprintf(fp_in, "%d ", rand() % 10000);
    }
    fclose(fp_in);
    printf("[+] Generated %d random elements and saved to '%s'.\n", n, infile);

    // 2. Read into array
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

    // 3. Apply Heap Sort
    heapSort(arr, n);
    printf("[+] Applied Heap Sort.\n");

    // 4. Validate the sorting
    if (validate_sort(arr, n)) {
        printf("[+] VALIDATION SUCCESS: The array is correctly sorted!\n");
    } else {
        printf("[-] VALIDATION FAILED: The array is not sorted properly.\n");
    }

    // 5. Write to output file
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

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

bool validate_sort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

// To heapify a subtree rooted with node i
void heapify(int *arr, int n, int i) {
    int largest = i; 
    int left = 2 * i + 1; 
    int right = 2 * i + 2; 

    if (left < n && arr[left] > arr[largest]) 
        largest = left;
    
    if (right < n && arr[right] > arr[largest]) 
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

// Main function to do heap sort
void heapSort(int *arr, int n) {
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]); // Move current root to end
        heapify(arr, i, 0);     // call max heapify on the reduced heap
    }
}