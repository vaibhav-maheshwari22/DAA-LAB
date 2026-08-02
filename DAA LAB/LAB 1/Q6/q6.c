#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Comparator function
int compareFunction(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {

    int n = 1000; 
    int arr[1000];
    int duplicate_found = 0;
    
    srand(time(NULL));
    
    // Populate array
    for(int i = 0; i < n; i++) {
        arr[i] = rand() % 5000; 
    }

    // Sort the array to bring duplicates adjacent to each other
    qsort(arr, n, sizeof(int), compareFunction);

    // Check for identical adjacent elements
    for(int i = 0; i < n - 1; i++) {
        if(arr[i] == arr[i+1]) {
            duplicate_found = 1;
            printf("Duplicate element found: %d (at indices %d and %d)\n", arr[i], i, i+1);
            break;
        }
    }

    if(!duplicate_found) {
        printf("No duplicate elements were found in the array.\n");
    }

    return 0;
}
