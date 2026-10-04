/*
 DAA Lab 08 - Q8: Optimal Binary Search Tree (OBST)

 Input:
   - n = number of keys
   - p[1..n] = probabilities of successful searches
   - q[0..n] = probabilities of unsuccessful (dummy) searches

 Output:
   Minimum expected search cost + optimal BST structure printed

 Time Complexity: O(n^3)
   3 nested loops: length l (1..n), start i, root r (i..j).
   Total iterations ~ n^3/6.

 Space Complexity: O(n^2)
   Three 2D tables e, w, root of size (n+2) x (n+1).
*/

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define MAX_KEYS 100

// Recursively print the optimal BST structure
void printOptimalBST(int root[][MAX_KEYS], int i, int j, int parent, int is_left) {
    if (i > j) {
        // Dummy key reached
        if (parent == 0) {
            printf("d%d is the root (empty tree)\n", j);
        } else if (is_left) {
            printf("d%d is the left child of k%d\n", j, parent);
        } else {
            printf("d%d is the right child of k%d\n", j, parent);
        }
        return;
    }

    int r = root[i][j];

    if (parent == 0) {
        printf("k%d is the root of the tree\n", r);
    } else if (is_left) {
        printf("k%d is the left child of k%d\n", r, parent);
    } else {
        printf("k%d is the right child of k%d\n", r, parent);
    }

    // Left and right subtrees
    printOptimalBST(root, i, r - 1, r, 1);
    printOptimalBST(root, r + 1, j, r, 0);
}

void optimalBST(double p[], double q[], int n) {
    // 1-based indexing, tables need n+2 rows
    double e[MAX_KEYS][MAX_KEYS];
    double w[MAX_KEYS][MAX_KEYS];
    int root[MAX_KEYS][MAX_KEYS];

    // Base case: subtrees with 0 keys (only dummy key d_{i-1})
    for (int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    // l = subtree length (number of keys)
    for (int l = 1; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;

            e[i][j] = DBL_MAX;
            // w[i][j] = w[i][j-1] + p[j] + q[j]
            w[i][j] = w[i][j - 1] + p[j] + q[j];

            // Try each key r as root
            for (int r = i; r <= j; r++) {
                // e[i][j] = min(e[i][r-1] + e[r+1][j] + w[i][j])
                double cost = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (cost < e[i][j]) {
                    e[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }

    // Print expected cost table
    printf("\n--- Expected Search Cost Table e[i][j] ---\n");
    printf("   j=");
    for (int j = 0; j <= n; j++) printf("%8d", j);
    printf("\n");
    for (int i = 1; i <= n + 1; i++) {
        printf("i=%2d:", i);
        for (int j = 0; j <= n; j++) {
            if (j >= i - 1)
                printf("%8.4f", e[i][j]);
            else
                printf("        ");
        }
        printf("\n");
    }

    // Print root table
    printf("\n--- Optimal Root Table root[i][j] ---\n");
    printf("   j=");
    for (int j = 1; j <= n; j++) printf("%5d", j);
    printf("\n");
    for (int i = 1; i <= n; i++) {
        printf("i=%2d:", i);
        for (int j = 1; j <= n; j++) {
            if (j >= i)
                printf("%5d", root[i][j]);
            else
                printf("     ");
        }
        printf("\n");
    }

    printf("\nMinimum Expected Search Cost: %.4f\n", e[1][n]);

    // Print tree structure
    printf("\n--- Optimal Binary Search Tree Structure ---\n");
    printOptimalBST(root, 1, n, 0, 0);
    printf("--------------------------------------------\n");
}

int main() {
    int n;

    printf("====================================================\n");
    printf("       Optimal Binary Search Trees (OBST)           \n");
    printf("====================================================\n");

    printf("Enter number of keys (n): ");
    if (scanf("%d", &n) != 1 || n <= 0 || n >= MAX_KEYS - 2) {
        printf("Invalid number of keys.\n");
        return 1;
    }

    double p[MAX_KEYS];
    double q[MAX_KEYS];

    printf("Enter probabilities p[1..%d] for successful searches:\n", n);
    for (int i = 1; i <= n; i++) {
        printf("  p[%d]: ", i);
        scanf("%lf", &p[i]);
    }

    printf("Enter probabilities q[0..%d] for dummy keys (unsuccessful searches):\n", n);
    for (int i = 0; i <= n; i++) {
        printf("  q[%d]: ", i);
        scanf("%lf", &q[i]);
    }

    optimalBST(p, q, n);

    return 0;
}