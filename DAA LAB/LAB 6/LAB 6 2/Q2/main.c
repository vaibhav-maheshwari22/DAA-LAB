#include <stdio.h>

/* Time Complexity: O(N * W) | Space Complexity: O(N * W) */
int main(void) {
    int n, capacity;
    printf("Enter number of items: ");
    scanf("%d", &n);
    printf("Enter knapsack capacity (W): ");
    scanf("%d", &capacity);

    int weight[n], profit[n];
    int best[n + 1][capacity + 1];

    printf("Enter weights of %d items: ", n);
    for (int i = 0; i < n; i++) scanf("%d", &weight[i]);

    printf("Enter profits of %d items: ", n);
    for (int i = 0; i < n; i++) scanf("%d", &profit[i]);

    for (int i = 0; i <= n; i++) {
        for (int current = 0; current <= capacity; current++) {
            if (i == 0 || current == 0) {
                best[i][current] = 0;
            } else if (weight[i - 1] <= current) {
                int included = profit[i - 1] + best[i - 1][current - weight[i - 1]];
                int excluded = best[i - 1][current];
                best[i][current] = (included > excluded) ? included : excluded;
            } else {
                best[i][current] = best[i - 1][current];
            }
        }
    }

    printf("Maximum Profit: %d\n", best[n][capacity]);
    return 0;
}