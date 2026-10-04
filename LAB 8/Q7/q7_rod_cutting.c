/*
 DAA Lab 08 - Q7: Rod Cutting with Reconstruction

 Input:
   - n = rod length
   - n prices (price of piece of length 1..n)

 Output:
   - Maximum revenue obtainable
   - Exact piece lengths that give that revenue

 Time Complexity: O(n^2)
   For each length j (1..n), inner loop tries cuts i=1..j.
   Total iterations = n(n+1)/2.
   Reconstruction takes O(n).

 Space Complexity: O(n)
   revenue[] and first_cut[] arrays of size n+1.
*/

#include <stdio.h>
#include <stdlib.h>

void rodCutting(int price[], int n) {
    // revenue[j] = max revenue for rod of length j
    int *revenue = (int *)malloc((n + 1) * sizeof(int));

    // first_cut[j] = best first cut length for rod of length j
    int *first_cut = (int *)malloc((n + 1) * sizeof(int));

    if (revenue == NULL || first_cut == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    // Base: rod of length 0 gives 0 revenue
    revenue[0] = 0;
    first_cut[0] = 0;

    // Build revenue table from length 1 to n
    for (int j = 1; j <= n; j++) {
        int max_val = -1;
        int best_cut = -1;

        // Try every possible first cut of length i
        for (int i = 1; i <= j; i++) {
            // revenue[j] = max(price[i-1] + revenue[j-i])
            int curr = price[i - 1] + revenue[j - i];
            if (curr > max_val) {
                max_val = curr;
                best_cut = i;
            }
        }

        revenue[j] = max_val;
        first_cut[j] = best_cut;
    }

    // Print DP table
    printf("\n--- DP Table (Rod Length -> Max Revenue & First Cut) ---\n");
    printf("Length:    ");
    for (int j = 0; j <= n; j++) printf("%4d ", j);
    printf("\nRevenue:   ");
    for (int j = 0; j <= n; j++) printf("%4d ", revenue[j]);
    printf("\nFirst Cut: ");
    for (int j = 0; j <= n; j++) printf("%4d ", first_cut[j]);
    printf("\n--------------------------------------------------------\n");

    // (i) Max revenue
    printf("\n(i) Maximum Revenue Obtainable: %d\n", revenue[n]);

    // (ii) Reconstruct pieces using first_cut
    printf("(ii) Optimal Piece Lengths (Reconstruction): [ ");
    int temp = n;
    int piece_count = 0;
    while (temp > 0) {
        int cut = first_cut[temp];
        printf("%d ", cut);
        temp -= cut;
        piece_count++;
    }
    printf("]\n");
    printf("     Total pieces cut: %d (Sum of pieces = %d)\n", piece_count, n);

    free(revenue);
    free(first_cut);
}

int main() {
    int n;

    printf("====================================================\n");
    printf("     Rod Cutting with Piece Length Reconstruction   \n");
    printf("====================================================\n");

    printf("Enter total length of the rod (n inches): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid rod length.\n");
        return 1;
    }

    int *price = (int *)malloc(n * sizeof(int));
    if (price == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter prices for rod lengths from 1 to %d:\n", n);
    for (int i = 0; i < n; i++) {
        printf("  Price for length %2d: ", i + 1);
        scanf("%d", &price[i]);
    }

    rodCutting(price, n);

    free(price);
    return 0;
}