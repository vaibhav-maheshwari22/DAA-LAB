/*
 * Description: 1D Array operations and their worst-case complexities.
 * 
 * Complexity Analysis:
 * (i)   Max Element: O(n) - Single linear scan.
 * (ii)  1st & 2nd Largest: O(n) - Single linear scan with two trackers.
 * (iii) Mean: O(n) - Single linear scan for sum.
 * (iv)  Median: O(n^2) worst-case, O(n) average - QuickSelect algorithm.
 * (v)   Standard Deviation: O(n) - Two passes (one for mean, one for variance).
 * (vi)  Mode: O(n log n) - Sorting takes O(n log n), followed by O(n) scan.
 * (vii) Remove Duplicates: O(n log n) - Sorting followed by O(n) compression.
 * (viii) Reverse Array: O(n) - Swapping elements from ends to middle.
 * (ix)  Custom Partition: O(n) - Single pass Lomuto-style partition.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Utility Functions
void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }
void copy_array(int *src, int *dest, int n) {
    for (int i = 0; i < n; i++) dest[i] = src[i];
}
int compare(const void *a, const void *b) { return (*(int*)a - *(int*)b); }

// (i) Max Element
int get_max(int *arr, int n) {
    int max_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) max_val = arr[i];
    }
    return max_val;
}

// (ii) 1st and 2nd Largest
void get_two_largest(int *arr, int n, int *first, int *second) {
    *first = arr[0];
    *second = -2147483648; // Minimum possible int
    for (int i = 1; i < n; i++) {
        if (arr[i] > *first) {
            *second = *first;
            *first = arr[i];
        } else if (arr[i] > *second && arr[i] != *first) {
            *second = arr[i];
        }
    }
}

// (iii) Mean
double get_mean(int *arr, int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    return (double)sum / n;
}

// (iv) Median (using QuickSelect logic on a copied array)
int partition_asc(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = low;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[high]);
    return i;
}
int quick_select(int *arr, int low, int high, int k) {
    if (low <= high) {
        int pi = partition_asc(arr, low, high);
        if (pi == k) return arr[pi];
        if (pi > k) return quick_select(arr, low, pi - 1, k);
        return quick_select(arr, pi + 1, high, k);
    }
    return -1;
}

// (v) Standard Deviation
double get_std_dev(int *arr, int n, double mean) {
    double variance_sum = 0;
    for (int i = 0; i < n; i++) {
        variance_sum += pow(arr[i] - mean, 2);
    }
    return sqrt(variance_sum / n);
}

// (vi) Mode (assumes sorted array)
int get_mode_sorted(int *arr, int n) {
    int mode = arr[0], max_count = 1, current_count = 1;
    for (int i = 1; i < n; i++) {
        if (arr[i] == arr[i - 1]) {
            current_count++;
        } else {
            if (current_count > max_count) {
                max_count = current_count;
                mode = arr[i - 1];
            }
            current_count = 1;
        }
    }
    if (current_count > max_count) mode = arr[n - 1];
    return mode;
}

// (vii) Remove Duplicates (assumes sorted array)
int remove_duplicates_sorted(int *arr, int n) {
    if (n == 0 || n == 1) return n;
    int j = 0;
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] != arr[i + 1]) {
            arr[j++] = arr[i];
        }
    }
    arr[j++] = arr[n - 1];
    return j; // New size
}

// (viii) Reverse Array
void reverse_array(int *arr, int n) {
    int start = 0, end = n - 1;
    while (start < end) {
        swap(&arr[start], &arr[end]);
        start++;
        end--;
    }
}

// (ix) Custom Partition (Elements < pivot AFTER elements >= pivot)
void custom_partition(int *arr, int n) {
    int pivot_idx = rand() % n;
    int pivot = arr[pivot_idx];
    
    // Move pivot to the end temporarily
    swap(&arr[pivot_idx], &arr[n - 1]);
    
    int i = 0;
    // We want >= pivot on the left, so we check for >=
    for (int j = 0; j < n - 1; j++) {
        if (arr[j] >= pivot) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[n - 1]);
    printf("Partitioned around pivot %d: ", pivot);
    for (int k = 0; k < n; k++) printf("%d ", arr[k]);
    printf("\n");
}

int main() {
    int n;
    srand(time(NULL));

    printf("1D Array Operations\n-------------------\n");
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    int *arr = (int *)malloc(n * sizeof(int));
    int *temp = (int *)malloc(n * sizeof(int));

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    // (i)
    printf("\n(i) Max Element: %d\n", get_max(arr, n));

    // (ii)
    int first, second;
    get_two_largest(arr, n, &first, &second);
    printf("(ii) 1st Largest: %d, 2nd Largest: %d\n", first, second);

    // (iii) & (v)
    double mean = get_mean(arr, n);
    printf("(iii) Mean: %.2f\n", mean);
    printf("(v) Standard Deviation: %.2f\n", get_std_dev(arr, n, mean));

    // (iv)
    copy_array(arr, temp, n);
    printf("(iv) Median: %d\n", quick_select(temp, 0, n - 1, n / 2));

    // (vi)
    copy_array(arr, temp, n);
    qsort(temp, n, sizeof(int), compare);
    printf("(vi) Mode: %d\n", get_mode_sorted(temp, n));

    // (vii)
    int new_size = remove_duplicates_sorted(temp, n);
    printf("(vii) Array after removing duplicates: ");
    for (int i = 0; i < new_size; i++) printf("%d ", temp[i]);
    printf("\n");

    // (viii)
    copy_array(arr, temp, n);
    reverse_array(temp, n);
    printf("(viii) Reversed Array: ");
    for (int i = 0; i < n; i++) printf("%d ", temp[i]);
    printf("\n");

    // (ix)
    copy_array(arr, temp, n);
    printf("(ix) ");
    custom_partition(temp, n);

    free(arr);
    free(temp);
    return 0;
}