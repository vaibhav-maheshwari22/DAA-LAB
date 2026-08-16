#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZES 6

// Global variables to track operations
long long cmps = 0;

static int n_vals[SIZES] = {16, 64, 256, 1024, 2048, 4096};

void assert_invariant(int *a, int n, int i);
void selection_sort(int *a, int n);
void fill_array(int *a, int n, int kind);
void run_test(int n, int kind, long long *c);

int main() {
    srand(time(0));
    
    printf("\n=================================================================\n");
    printf(" SELECTION SORT: INVARIANT VALIDATION & COMPLEXITY\n");
    printf("=================================================================\n");
    printf("%-6s | %-12s | %-12s | %-12s | %-12s\n", "N", "Sorted", "Reverse", "Random", "Exact n(n-1)/2");
    printf("-----------------------------------------------------------------\n");
    
    FILE *fp = fopen("q6_data.csv", "w");
    if (fp) fprintf(fp, "N,Sorted,Reverse,Random,Exact\n");
    
    for (int i = 0; i < SIZES; i++) {
        int n = n_vals[i];
        long long c_sort, c_rev, c_rand;
        
        run_test(n, 0, &c_sort); // 0 = Sorted
        run_test(n, 1, &c_rev);  // 1 = Reverse
        run_test(n, 2, &c_rand); // 2 = Random
        
        long long exact = (long long)n * (n - 1) / 2;
        
        printf("%-6d | %-12lld | %-12lld | %-12lld | %-12lld\n", 
               n, c_sort, c_rev, c_rand, exact);
               
        if (fp) fprintf(fp, "%d,%lld,%lld,%lld,%lld\n", n, c_sort, c_rev, c_rand, exact);
    }
    
    if (fp) fclose(fp);
    
    printf("\nConclusion: Invariants successfully held across all iterations.\n");
    printf("Comparisons strictly remain Theta(n^2) regardless of the input order.\n");
    
    return 0;
}

// Validates Initialization, Maintenance, and Termination dynamically
void assert_invariant(int *a, int n, int i) {
    // 1. Prefix must be sorted
    for (int k = 1; k < i; k++) {
        if (a[k-1] > a[k]) { 
            printf("Error: Prefix unsorted!\n"); 
            exit(1); 
        }
    }
    // 2. No element in suffix can be smaller than the largest in prefix
    if (i > 0) {
        for (int k = i; k < n; k++) {
            if (a[k] < a[i-1]) { 
                printf("Error: Suffix invalid!\n"); 
                exit(1); 
            }
        }
    }
}

void selection_sort(int *a, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        assert_invariant(a, n, i); // Maintenance Check
        
        for (int j = i + 1; j < n; j++) {
            cmps++;
            if (a[j] < a[min_idx]) min_idx = j;
        }
        
        if (min_idx != i) {
            int temp = a[i];
            a[i] = a[min_idx];
            a[min_idx] = temp;
        }
    }
    assert_invariant(a, n, n); // Termination Check
}

// Generates array based on kind: 0=Sorted, 1=Reverse, 2=Random
void fill_array(int *a, int n, int kind) {
    for (int i = 0; i < n; i++) {
        if (kind == 0) a[i] = i;
        else if (kind == 1) a[i] = n - i;
        else a[i] = rand() % 10000;
    }
}

void run_test(int n, int kind, long long *c) {
    int *a = (int *)malloc(n * sizeof(int));
    cmps = 0;
    
    fill_array(a, n, kind);
    
    assert_invariant(a, n, 0); // Initialization Check
    selection_sort(a, n);
    
    *c = cmps;
    free(a);
}