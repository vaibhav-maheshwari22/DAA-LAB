/*
 * Description: Sorting via reversal procedure.
 * Validates both Part 1 (O(n) reversals) and Part 2 (O(n log^2 n) cost).
 */

#include <stdio.h>
#include <stdlib.h>

long long total_cost = 0;
int total_reversals = 0;

// Utility to copy array
void copy_array(int *src, int *dest, int n) {
    for (int i = 0; i < n; i++) dest[i] = src[i];
}

// ---------------------------------------------------------
// PART 1: O(n) Reversals Algorithm (Selection Sort Logic)
// ---------------------------------------------------------
void reverse_part1(int *arr, int i, int j) {
    if (i >= j) return;
    total_reversals++; // Counting the NUMBER of reversals
    while (i < j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        i++;
        j--;
    }
}

void sort_part1_On_reversals(int *arr, int n) {
    for (int k = n - 1; k > 0; k--) {
        // Find max element in arr[0...k]
        int max_idx = 0;
        for (int i = 1; i <= k; i++) {
            if (arr[i] > arr[max_idx]) {
                max_idx = i;
            }
        }
        // If max is not already at the end of the current boundary
        if (max_idx != k) {
            // Move max to front (if not already there)
            if (max_idx != 0) {
                reverse_part1(arr, 0, max_idx);
            }
            // Move max from front to position k
            reverse_part1(arr, 0, k);
        }
    }
}


// ---------------------------------------------------------
// PART 2: O(n log^2 n) Cost Algorithm (In-Place Merge Sort)
// ---------------------------------------------------------
void reverse_part2(int *arr, int i, int j) {
    if (i >= j) return;
    total_cost += (j - i + 1); // Cost is the LENGTH of the reversed range
    
    while (i < j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        i++;
        j--;
    }
}

void rotate(int *arr, int left, int mid, int right) {
    if (left > mid || mid >= right) return;
    reverse_part2(arr, left, mid);
    reverse_part2(arr, mid + 1, right);
    reverse_part2(arr, left, right);
}

int bin_search(int *arr, int low, int high, int key) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return low;
}

void merge_rev(int *arr, int left, int mid, int right) {
    if (left > mid || mid >= right) return;
    if (arr[mid] <= arr[mid + 1]) return; 

    int len1 = mid - left + 1;
    int len2 = right - mid;
    int m1, m2;

    if (len1 <= len2) {
        m1 = left + len1 / 2;
        m2 = bin_search(arr, mid + 1, right, arr[m1]);
    } else {
        m2 = mid + 1 + len2 / 2;
        m1 = bin_search(arr, left, mid, arr[m2]);
    }

    rotate(arr, m1, mid, m2 - 1);
    int new_mid = m1 + (m2 - 1 - mid);

    merge_rev(arr, left, m1 - 1, new_mid - 1);
    merge_rev(arr, new_mid + 1, m2 - 1, right);
}

void sort_part2_cost(int *arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        sort_part2_cost(arr, left, mid);
        sort_part2_cost(arr, mid + 1, right);
        merge_rev(arr, left, mid, right);
    }
}

// ---------------------------------------------------------
// MAIN FUNCTION
// ---------------------------------------------------------
int main() {
    int n;

    printf("Sorting via Reversal Procedure\n");
    printf("------------------------------\n");
    printf("Enter number of elements (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    int *arr = (int *)malloc(n * sizeof(int));
    int *temp = (int *)malloc(n * sizeof(int));
    
    if (!arr || !temp) return 1;

    printf("Enter %d integers (permutation):\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // --- Execute Part 1 ---
    copy_array(arr, temp, n);
    sort_part1_On_reversals(temp, n);
    printf("\n[Part 1] O(n) Reversals Strategy\n");
    printf("Total Reversals Used: %d (Bounded by 2n = %d)\n", total_reversals, 2 * n);

    // --- Execute Part 2 ---
    copy_array(arr, temp, n);
    sort_part2_cost(temp, 0, n - 1);
    printf("\n[Part 2] O(n log^2 n) Cost Strategy\n");
    printf("Total Cost (Sum of lengths): %lld\n", total_cost);

    printf("\nSorted Array Verification: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", temp[i]);
    }
    printf("\n");

    free(arr);
    free(temp);
    return 0;
}