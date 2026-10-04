/*
 DAA Lab 08 - Q3: Longest Common Subsequence with Reconstruction

 Input:
   - Two strings X and Y

 Time Complexity: O(m * n)
   Filling (m+1) x (n+1) DP table + O(m+n) backtrack.

 Space Complexity: O(m * n)
   2D dp array.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1024

int max(int a, int b) {
    return (a > b) ? a : b;
}

void findLCS(char X[], char Y[]) {
    int m = strlen(X);
    int n = strlen(Y);
    int i, j;

    // dp[i][j] = LCS length of X[0..i-1] and Y[0..j-1]
    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    for (i = 0; i <= m; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
    }

    // Fill DP table
    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    // Print DP table with character headers
    printf("\n--- 2D DP Table (Dimensions: %d x %d) ---\n", m + 1, n + 1);
    printf("       ");
    for (j = 0; j < n; j++) printf("  %c", Y[j]);
    printf("\n");

    for (i = 0; i <= m; i++) {
        if (i == 0) printf("   ");
        else printf(" %c ", X[i - 1]);
        for (j = 0; j <= n; j++) {
            printf("%3d", dp[i][j]);
        }
        printf("\n");
    }
    printf("-----------------------------------------\n");

    int lcs_len = dp[m][n];
    printf("\nLength of Longest Common Subsequence: %d\n", lcs_len);

    // Backtrack to reconstruct LCS
    char *lcs = (char *)malloc((lcs_len + 1) * sizeof(char));
    lcs[lcs_len] = '\0';
    i = m;
    j = n;
    int idx = lcs_len - 1;

    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[idx--] = X[i - 1];
            i--;
            j--;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    printf("Reconstructed LCS: \"%s\"\n", lcs);

    free(lcs);
    for (i = 0; i <= m; i++) free(dp[i]);
    free(dp);
}

int main() {
    char X[MAX_LEN], Y[MAX_LEN];

    printf("============================================================\n");
    printf("  Longest Common Subsequence (LCS) with Reconstruction      \n");
    printf("============================================================\n");

    printf("Enter first sequence (String X): ");
    if (scanf("%s", X) != 1) {
        printf("Error reading String X.\n");
        return 1;
    }

    printf("Enter second sequence (String Y): ");
    if (scanf("%s", Y) != 1) {
        printf("Error reading String Y.\n");
        return 1;
    }

    findLCS(X, Y);
    return 0;
}