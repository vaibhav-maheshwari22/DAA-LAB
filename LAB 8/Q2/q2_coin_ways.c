/*
 DAA Lab 08 - Q2: Coin Change - Total Number of Ways

 Input:
   - n = number of distinct coins
   - n coin values
   - V = target amount

 Time Complexity: O(n * V)
   Outer loop over coins, inner loop over amounts.

 Space Complexity: O(V)
   Single dp array of size V+1.
*/

#include <stdio.h>
#include <stdlib.h>

long long countWays(int coins[], int n, int V) {
    int i, j;

    // dp[j] = number of ways to make amount j
    unsigned long long *dp = (unsigned long long *)calloc(V + 1, sizeof(unsigned long long));

    if (dp == NULL) {
        printf("Memory allocation failed!\n");
        return 0;
    }

    // Base: one way to make 0 (pick nothing)
    dp[0] = 1;

    // Outer loop over coins -> combinations, not permutations
    for (i = 0; i < n; i++) {
        int c = coins[i];
        // dp[j] = dp[j] + dp[j - c]
        for (j = c; j <= V; j++) {
            dp[j] += dp[j - c];
        }
    }

    // Print DP table
    printf("\n--- DP Table State (Amount -> Distinct Ways) ---\n");
    for (j = 0; j <= V; j++) {
        printf("Amount %2d : %llu ways\n", j, dp[j]);
    }
    printf("------------------------------------------------\n");

    unsigned long long total = dp[V];
    free(dp);
    return total;
}

int main() {
    int n, V, i;

    printf("====================================================\n");
    printf("  Coin Change: Total Number of Ways (Combinations)  \n");
    printf("====================================================\n");

    printf("Enter number of distinct coin denominations: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of coins.\n");
        return 1;
    }

    int *coins = (int *)malloc(n * sizeof(int));
    if (coins == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter the %d distinct coin denominations: ", n);
    for (i = 0; i < n; i++) scanf("%d", &coins[i]);

    printf("Enter target amount V: ");
    if (scanf("%d", &V) != 1 || V < 0) {
        printf("Invalid target amount.\n");
        free(coins);
        return 1;
    }

    unsigned long long result = countWays(coins, n, V);
    printf("\nTotal number of distinct combinations to form %d is: %llu\n", V, result);

    free(coins);
    return 0;
}