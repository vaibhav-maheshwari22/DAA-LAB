/*
 * Description: algorithm to merge overlapping intervals.
 */

#include <stdio.h>
#include <stdlib.h>

// Struct 
typedef struct {
    int start;
    int end;
} Interval;

void get_data(Interval *arr, int n);
int compare_intervals(const void *a, const void *b);
void merge_intervals(Interval *arr, int n);

int main() {
    int n;

    printf("Merge Overlapping Intervals\n");
    printf("---------------------------\n");
    printf("Enter the number of intervals (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size!\n");
        return 1;
    }

    // Dynamically allocate memory
    Interval *arr = (Interval *)malloc(n * sizeof(Interval));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Take input from the user
    get_data(arr, n);

    // Sort the intervals
    qsort(arr, n, sizeof(Interval), compare_intervals);

    // Merge and print overlapping intervals
    merge_intervals(arr, n);

    // Free the allocated memory
    free(arr);
    return 0;
}

// User input function
void get_data(Interval *arr, int n) {
    printf("\nEnter %d intervals (start and end):\n", n);
    for (int i = 0; i < n; i++) {
        printf("Interval %d: ", i + 1);
        scanf("%d %d", &arr[i].start, &arr[i].end);
    }
}

// Comparator function for qsort (sort by start time)
int compare_intervals(const void *a, const void *b) {
    Interval *i1 = (Interval *)a;
    Interval *i2 = (Interval *)b;
    return (i1->start - i2->start);
}

// Logic to merge overlapping intervals
void merge_intervals(Interval *arr, int n) {
    // Array to store merged intervals
    Interval *merged = (Interval *)malloc(n * sizeof(Interval));
    if (merged == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    int count = 0;

    // First interval goes directly into the merged list
    merged[0] = arr[0];
    count++;

    for (int i = 1; i < n; i++) {
        // If current interval overlaps with the last merged interval
        if (arr[i].start <= merged[count - 1].end) {
            // Update the end time to the maximum of both
            if (arr[i].end > merged[count - 1].end) {
                merged[count - 1].end = arr[i].end;
            }
        } else {
            // No overlap, add it to the merged list
            merged[count] = arr[i];
            count++;
        }
    }

    // Print the result
    printf("\nResult: Merged Intervals:\n{ ");
    for (int i = 0; i < count; i++) {
        printf("(%d, %d) ", merged[i].start, merged[i].end);
    }
    printf("}\n");

    free(merged);
}