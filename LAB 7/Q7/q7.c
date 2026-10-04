#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void matrix_chain_order(int *p, int n, long long ***m, int ***s);
void print_optimal_parens(int **s, int i, int j);
void get_data(int **p, int *n);
void display_results(long long min_cost, int **s, int n);

int main(void) {
    int n;
    int *p = NULL;
    long long **m = NULL;
    int **s = NULL;

    printf("Matrix Chain Multiplication (DP)\n");
    get_data(&p, &n);

    matrix_chain_order(p, n, &m, &s);

    display_results(m[1][n], s, n);

    // Free memory
    for (int i = 0; i <= n; i++) {
        free(m[i]);
        free(s[i]);
    }
    free(m);
    free(s);
    free(p);

    return 0;
}

// Computes the minimum multiplication costs and tracks split points
void matrix_chain_order(int *p, int n, long long ***m, int ***s) {
    *m = (long long **)malloc((n + 1) * sizeof(long long *));
    *s = (int **)malloc((n + 1) * sizeof(int *));

    if (*m == NULL || *s == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (int i = 0; i <= n; i++) {
        (*m)[i] = (long long *)malloc((n + 1) * sizeof(long long));
        (*s)[i] = (int *)malloc((n + 1) * sizeof(int));
        if ((*m)[i] == NULL || (*s)[i] == NULL) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
        (*m)[i][i] = 0; // Cost of a single matrix is zero
    }

    // len is chain length (from 2 matrices up to n matrices)
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            (*m)[i][j] = LLONG_MAX;

            for (int k = i; k < j; k++) {
                long long cost = (*m)[i][k] + (*m)[k + 1][j] + (long long)p[i - 1] * p[k] * p[j];
                if (cost < (*m)[i][j]) {
                    (*m)[i][j] = cost;
                    (*s)[i][j] = k; // Record optimal split point
                }
            }
        }
    }
}

// Reconstructs the parenthesization recursively
void print_optimal_parens(int **s, int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        print_optimal_parens(s, i, s[i][j]);
        print_optimal_parens(s, s[i][j] + 1, j);
        printf(")");
    }
}

void get_data(int **p, int *n) {
    printf("Enter number of matrices: ");
    while (scanf("%d", n) != 1 || *n <= 0) {
        printf("Invalid input! Please enter a positive integer: ");
        while (getchar() != '\n');
    }

    *p = (int *)malloc((*n + 1) * sizeof(int));
    if (*p == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    printf("Enter %d dimensions :\n", *n + 1);
    for (int i = 0; i <= *n; i++) {
        printf("p[%d]: ", i);
        while (scanf("%d", &(*p)[i]) != 1 || (*p)[i] <= 0) {
            printf("Invalid dimension! Enter a positive value for p[%d]: ", i);
            while (getchar() != '\n');
        }
    }
    printf("\n");
}

void display_results(long long min_cost, int **s, int n) {
    printf("MCM Optimization Results \n");
    printf("Minimum Scalar Multiplications: %lld\n", min_cost);
    printf("Optimal Parenthesization       : ");
    print_optimal_parens(s, 1, n);
    printf("\n");
}