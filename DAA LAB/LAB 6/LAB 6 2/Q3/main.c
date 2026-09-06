#include <stdio.h>
#include <string.h>

/* Time Complexity: O(M * N) | Space Complexity: O(M * N) */
int main(void) {
    char first[1000], second[1000];
    printf("Enter first string: ");
    scanf("%999s", first);
    printf("Enter second string: ");
    scanf("%999s", second);

    int m = (int)strlen(first);
    int n = (int)strlen(second);
    int length[m + 1][n + 1];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                length[i][j] = 0;
            else if (first[i - 1] == second[j - 1])
                length[i][j] = length[i - 1][j - 1] + 1;
            else
                length[i][j] = (length[i - 1][j] > length[i][j - 1]) ? length[i - 1][j] : length[i][j - 1];
        }
    }

    int size = length[m][n];
    char subsequence[size + 1];
    subsequence[size] = '\0';

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (first[i - 1] == second[j - 1]) {
            subsequence[--size] = first[i - 1];
            i--; j--;
        } else if (length[i - 1][j] > length[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    printf("Length of LCS: %d\n", length[m][n]);
    printf("Longest Common Subsequence: %s\n", subsequence);
    return 0;
}