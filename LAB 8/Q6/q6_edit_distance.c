/*
 * File: q6_edit_distance.c
 * Input: string A of length m, string B of length n
 * Time Complexity: O(m * n)
 * Space Complexity: O(m * n)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1024

int min3(int a, int b, int c) {
    int m = a;
    if (b < m) m = b;
    if (c < m) m = c;
    return m;
}

typedef struct {
    char action[64];
} EditStep;

void computeEditDistance(char A[], char B[]) {
    int m = strlen(A);
    int n = strlen(B);

    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
    }

    // Base cases: deleting i chars or inserting j chars
    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;

    // Fill table bottom-up
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (A[i - 1] == B[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                // DP transition: 1 + min(delete, insert, substitute)
                dp[i][j] = 1 + min3(dp[i - 1][j],
                                    dp[i][j - 1],
                                    dp[i - 1][j - 1]);
            }
        }
    }

    // Print DP table
    printf("\n--- 2D DP Table ---\n");
    printf("        #");
    for (int j = 0; j < n; j++) printf("  %c", B[j]);
    printf("\n");

    for (int i = 0; i <= m; i++) {
        if (i == 0) printf(" # ");
        else printf(" %c ", A[i - 1]);

        for (int j = 0; j <= n; j++) {
            printf("%3d", dp[i][j]);
        }
        printf("\n");
    }
    printf("----------------------------------------\n");

    printf("\nMin Edit Distance: %d\n", dp[m][n]);

    // Traceback operations
    EditStep *steps = (EditStep *)malloc((m + n + 1) * sizeof(EditStep));
    int step_count = 0;
    int i = m, j = n;

    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && A[i - 1] == B[j - 1] &&
            dp[i][j] == dp[i - 1][j - 1]) {
            snprintf(steps[step_count++].action, 64,
                     "Keep '%c' (Match)", A[i - 1]);
            i--; j--;
        }
        else if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1) {
            snprintf(steps[step_count++].action, 64,
                     "Substitute '%c' with '%c'", A[i - 1], B[j - 1]);
            i--; j--;
        }
        else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1) {
            snprintf(steps[step_count++].action, 64,
                     "Delete '%c' from A", A[i - 1]);
            i--;
        }
        else if (j > 0 && dp[i][j] == dp[i][j - 1] + 1) {
            snprintf(steps[step_count++].action, 64,
                     "Insert '%c' into A", B[j - 1]);
            j--;
        }
    }

    printf("\n--- Step-by-Step Traceback ---\n");
    int op_num = 1;
    for (int k = step_count - 1; k >= 0; k--) {
        printf("Step %2d: %s\n", op_num++, steps[k].action);
    }
    printf("----------------------------------------\n");

    free(steps);
    for (int r = 0; r <= m; r++) free(dp[r]);
    free(dp);
}

int main() {
    char A[MAX_LEN], B[MAX_LEN];

    printf("----------------------------------------\n");
    printf("  Edit Distance with Traceback\n");
    printf("----------------------------------------\n");

    printf("Enter source string A: ");
    if (scanf("%s", A) != 1) return 1;

    printf("Enter target string B: ");
    if (scanf("%s", B) != 1) return 1;

    computeEditDistance(A, B);
    return 0;
}
