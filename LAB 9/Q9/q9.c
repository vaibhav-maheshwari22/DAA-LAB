
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Print the tree structure in parenthesised form: (left,right)
static void printTree(int left, int right, int n, int *split) {
    if (left == right) {
        printf("%d", left + 1);
        return;
    }
    printf("(");
    printTree(left, split[left * n + right], n, split);
    printf(",");
    printTree(split[left * n + right] + 1, right, n, split);
    printf(")");
}

// Fill `levels[i]` with the depth of leaf i in the optimal tree
static void printDepths(int left, int right, int depth, int n,
                        int *split, int *levels) {
    if (left == right) {
        levels[left] = depth;
        return;
    }
    printDepths(left, split[left * n + right], depth + 1, n, split, levels);
    printDepths(split[left * n + right] + 1, right, depth + 1, n,
                split, levels);
}

static int solve(unsigned long long *w, int n) {
    size_t cells = (size_t)n * (size_t)n;

    // dp[i*n + j] = best cost for interval [i..j]
    // split[i*n + j] = optimal root split for interval [i..j]
    unsigned long long *dp = calloc(cells, sizeof(*dp));
    unsigned long long *prefix = malloc((size_t)(n + 1) * sizeof(*prefix));
    int *split  = malloc(cells * sizeof(*split));
    int *levels = malloc((size_t)n * sizeof(*levels));
    int length, i, j, k;

    if (!dp || !prefix || !split || !levels) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(dp); free(prefix); free(split); free(levels);
        return 0;
    }

    // Prefix sums for O(1) range sum queries
    prefix[0] = 0;
    for (i = 0; i < n; i++)
        prefix[i + 1] = prefix[i] + w[i];

    // Base case: single leaf → cost 0
    for (i = 0; i < n; i++)
        split[i * n + i] = i;

    // Fill DP table by increasing interval length
    for (length = 2; length <= n; length++) {
        for (i = 0; i + length <= n; i++) {
            unsigned long long sum;
            j = i + length - 1;
            sum = prefix[j + 1] - prefix[i];
            dp[i * n + j] = ULLONG_MAX;

            for (k = i; k < j; k++) {
                unsigned long long candidate =
                    dp[i * n + k] + dp[(k + 1) * n + j] + sum;
                if (candidate < dp[i * n + j]) {
                    dp[i * n + j] = candidate;
                    split[i * n + j] = k;
                }
            }
        }
    }

    printDepths(0, n - 1, 0, n, split, levels);

    printf("Minimum weighted depth: %llu\n", dp[n - 1]);
    printf("Alphabetic tree: ");
    printTree(0, n - 1, n, split);
    printf("\nIndex Weight Depth\n");
    for (i = 0; i < n; i++)
        printf("%d %llu %d\n", i + 1, w[i], levels[i]);

    free(dp); free(prefix); free(split); free(levels);
    return 1;
}

static int readWeights(unsigned long long **weights, int *count) {
    int n, i;
    size_t capacity = 0;
    unsigned long long *buffer = NULL;

    if (scanf("%d", &n) != 1 || n < 1 || n > 200) {
        fprintf(stderr, "Invalid weight count; require 1 <= n <= 200.\n");
        return 0;
    }

    for (i = 0; i < n; i++) {
        unsigned long long value;
        if (i == (int)capacity) {
            size_t next = capacity == 0 ? 4 : capacity * 2;
            unsigned long long *temp = realloc(buffer, next * sizeof(*buffer));
            if (!temp) {
                fprintf(stderr, "Memory allocation failed.\n");
                free(buffer);
                return 0;
            }
            buffer = temp;
            capacity = next;
        }
        if (scanf("%llu", &value) != 1 || value == 0) {
            fprintf(stderr, "Weights must be positive unsigned integers.\n");
            free(buffer);
            return 0;
        }
        buffer[i] = value;
    }

    *weights = buffer;
    *count = n;
    return 1;
}

int main(void) {
    int choice;
    for (;;) {
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid menu input.\n");
            return 1;
        }
        if (choice == 0) break;

        if (choice == 1) {
            unsigned long long *weights = NULL;
            int n;
            if (!readWeights(&weights, &n)) return 1;
            if (!solve(weights, n)) { free(weights); return 1; }
            free(weights);
        } else {
            printf("Invalid choice\n");
        }
    }
    return 0;
}