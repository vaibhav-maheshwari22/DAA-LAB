#include <stdio.h>

// Finds the first occurrence of '1' using Binary Search
int findTransition(int arr[], int n) {

    int low = 0, high = n - 1;
    
    while (low <= high) {

        int mid = low + (high - low) / 2;
        
        // If 0, the transition point must be on the right
        if (arr[mid] == 0) {
            low = mid + 1;
        } 
        
        else {

            // If 1, check if it is strictly the first '1'
            if (mid == 0 || arr[mid - 1] == 0) {
                return mid; 
            }
            
            // Otherwise, the first '1' is further left
            high = mid - 1;
        }
    }
    
    return -1; // if array contains no 1s
}

int main() {

    int arr[] = {0, 0, 0, 0, 1, 1, 1, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int transitionIndex = findTransition(arr, n);
    printf("Transition point (first '1') is at index: %d\n", transitionIndex);
    
    return 0;
}
