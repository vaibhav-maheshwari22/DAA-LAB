#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define SIZES 7
#define PROBES 400

// Global arrays to store average and worst-case comparison counts
int n_vals[SIZES] = {15, 63, 255, 1023, 4095, 16383, 65535};
double avg_bin[SIZES], avg_ter[SIZES];
long long wc_bin[SIZES], wc_ter[SIZES];

int binary_search(int *arr, int n, int target, long long *comps);
int ternary_search(int *arr, int n, int target, long long *comps);
int linear_find(int *arr, int n, int target);
void run_test(int idx);

int main()
{
    srand(time(0));

    // Run tests for all predefined array sizes
    for (int i = 0; i < SIZES; i++)
    {
        run_test(i);
    }

    // Print results
    printf("N\tBin Avg\tTer Avg\tBin WC\tTer WC\tRatio\n");
    printf("------------------------------------------------------\n");
    for (int i = 0; i < SIZES; i++)
    {
        printf("%d\t%.2f\t%.2f\t%lld\t%lld\t%.2f\n",
               n_vals[i], avg_bin[i], avg_ter[i], wc_bin[i], wc_ter[i],
               avg_ter[i] / avg_bin[i]);
    }

    // Export data to CSV
    FILE *fp = fopen("q1_search_data.csv", "w");
    if (!fp)
        return 1;

    fprintf(fp, "N,BinAvg,TerAvg,BinWC,TerWC\n");
    for (int i = 0; i < SIZES; i++)
    {
        fprintf(fp, "%d,%.2f,%.2f,%lld,%lld\n",
                n_vals[i], avg_bin[i], avg_ter[i], wc_bin[i], wc_ter[i]);
    }
    fclose(fp);

    return 0;
}

// Standard Binary Search
int binary_search(int *arr, int n, int target, long long *comps)
{
    int lo = 0, hi = n - 1;
    while (lo <= hi)
    {
        int mid = lo + (hi - lo) / 2;
        (*comps)++;
        if (arr[mid] == target)
            return mid;

        (*comps)++;
        if (arr[mid] < target)
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return -1;
}

// Ternary Search
int ternary_search(int *arr, int n, int target, long long *comps)
{
    int lo = 0, hi = n - 1;
    while (lo <= hi)
    {
        int third = (hi - lo) / 3;
        int m1 = lo + third;
        int m2 = hi - third;

        (*comps)++;
        if (arr[m1] == target)
            return m1;

        (*comps)++;
        if (m2 != m1 && arr[m2] == target)
            return m2;

        (*comps)++;
        if (target < arr[m1])
        {
            hi = m1 - 1;
            continue;
        }

        (*comps)++;
        if (target > arr[m2])
        {
            lo = m2 + 1;
            continue;
        }

        // Target is in the middle third
        lo = m1 + 1;
        hi = m2 - 1;
    }
    return -1;
}

// Simple linear search used as an validator
int linear_find(int *arr, int n, int target)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == target)
            return i;
    }
    return -1;
}

// Runs the testing logic
void run_test(int idx)
{
    int n = n_vals[idx];
    long long s_bin = 0, s_ter = 0;
    long long m_bin = 0, m_ter = 0;

    // Allocate and populate a sorted array
    int *arr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        arr[i] = 2 * i;

    // Probe random elements to calculate average and worst-case comparisons
    for (int i = 0; i < PROBES; i++)
    {
        // Alternate between testing elements that exist and those that don't
        int target = (i % 2) ? 2 * (rand() % n) : 2 * (rand() % n) + 1;

        long long c_bin = 0, c_ter = 0;
        int r_bin = binary_search(arr, n, target, &c_bin);
        int r_ter = ternary_search(arr, n, target, &c_ter);
        int exp = linear_find(arr, n, target);

        // Track maximum (worst-case) and sum (for average)
        if (c_bin > m_bin)
            m_bin = c_bin;
        s_bin += c_bin;

        if (c_ter > m_ter)
            m_ter = c_ter;
        s_ter += c_ter;

        // Cross-validate results to ensure correctness
        if ((exp < 0) != (r_bin < 0) || (exp < 0) != (r_ter < 0))
        {
            printf("Mismatch!\n");
            exit(1);
        }
    }

    avg_bin[idx] = (double)s_bin / PROBES;
    wc_bin[idx] = m_bin;
    avg_ter[idx] = (double)s_ter / PROBES;
    wc_ter[idx] = m_ter;

    free(arr);
}