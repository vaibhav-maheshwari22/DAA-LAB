/*
 DAA Lab 08 - Q1: Minimum Coin Change

 Input:
   - n = number of coin types
   - n coin values
   - V = target amount

 Time Complexity: O(n * V)
   For every amount 1..V, we check all n coins. Total work = n * V.

 Space Complexity: O(V)
   dp[V+1] and last[V+1].
*/

#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

int minCoins(int coins[], int n, int V) {
    int i, j;

    // dp[i] = minimum coins needed to make amount i
    int *dp = (int *)malloc((V + 1) * sizeof(int));

    // last[i] = last coin used to make amount i optimally
    int *last = (int *)malloc((V + 1) * sizeof(int));

    if (dp == NULL || last == NULL) {
        printf("Memory allocation failed!\n");
        return -1;
    }

    // Base: 0 amount needs 0 coins
    dp[0] = 0;
    last[0] = -1;

    // All other amounts start unreachable
    for (i = 1; i <= V; i++) {
        dp[i] = INF;
        last[i] = -1;
    }

    // Build dp from amount 1 to V
    for (i = 1; i <= V; i++) {
        for (j = 0; j < n; j++) {
            int c = coins[j];
            if (c <= i && dp[i - c] != INF) {
                if (1 + dp[i - c] < dp[i]) {
                    dp[i] = 1 + dp[i - c];
                    last[i] = c;
                }
            }
        }
    }

    // Print DP table state
    printf("\n--- DP Table State (Amount -> Min Coins Needed) ---\n");
    printf("Amount: ");
    for (i = 0; i <= V; i++) printf("%4d ", i);
    printf("\nCoins:  ");
    for (i = 0; i <= V; i++) {
        if (dp[i] == INF) printf(" INF ");
        else printf("%4d ", dp[i]);
    }
    printf("\n---------------------------------------------------\n");

    // Traceback coins
    if (dp[V] != INF) {
        printf("\nCoins used to form %d: ", V);
        int temp = V;
        while (temp > 0) {
            printf("%d ", last[temp]);
            temp -= last[temp];
        }
        printf("\n");
    }

    int ans = dp[V];
    free(dp);
    free(last);

    if (ans >= INF) return -1;
    return ans;
}

int main() {
    int n, V, i;

    printf("===========================================\n");
    printf("   Minimum Coin Change Problem (Lab 08)    \n");
    printf("===========================================\n");

    printf("Enter number of coin denominations: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of coins.\n");
        return 1;
    }

    int *coins = (int *)malloc(n * sizeof(int));
    if (coins == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter the %d coin denominations: ", n);
    for (i = 0; i < n; i++) scanf("%d", &coins[i]);

    printf("Enter target amount V: ");
    if (scanf("%d", &V) != 1 || V < 0) {
        printf("Invalid target amount.\n");
        free(coins);
        return 1;
    }

    int ans = minCoins(coins, n, V);

    if (ans == -1)
        printf("\nAmount %d cannot be made. Answer = -1\n", V);
    else
        printf("\nMinimum coins needed = %d\n", ans);

    free(coins);
    return 0;
}