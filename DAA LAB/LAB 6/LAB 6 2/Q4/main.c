#include <stdio.h>
#include <limits.h>

/* Time Complexity: O(N^3) | Space Complexity: O(N^2) */
int main(void) {
    int N;
    printf("Enter N (size of array): ");
    scanf("%d", &N);

    int arr[N];
    printf("Enter the dimensions array arr[] (e.g., 10 30 5 60): ");
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    // Number of matrices is N-1
    int n_matrices = N - 1; 
    long long cost[n_matrices][n_matrices];

    for (int i = 0; i < n_matrices; i++) {
        cost[i][i] = 0;
    }

    for (int length = 2; length <= n_matrices; length++) {
        for (int i = 0; i < n_matrices - length + 1; i++) {
            int j = i + length - 1;
            cost[i][j] = LLONG_MAX;

            for (int k = i; k < j; k++) {
                long long current = cost[i][k] + cost[k + 1][j] 
                                  + (long long)arr[i] * arr[k + 1] * arr[j + 1];
                if (current < cost[i][j]) {
                    cost[i][j] = current;
                }
            }
        }
    }

    printf("Output: %lld\n", cost[0][n_matrices - 1]);
    return 0;
}