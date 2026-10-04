#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NNS 6

int n_values[NNS] = {2, 4, 8, 16, 32, 64};
long long dc_mults = 0;
long long nav_mults = 0;

int** allocate_matrix(int n);
void free_matrix(int **matrix, int n);
void add_matrix(int **A, int **B, int **C, int n);
void sub_matrix(int **A, int **B, int **C, int n);
void multiply_special(int **A, int **B, int **C, int n);
void naive_multiply(int **A, int **B, int **C, int n);

int main() {
    printf("\n===========================================================\n");
    printf(" SPECIAL MATRIX MULTIPLICATION: O(n^2) vs NAIVE O(n^3)\n");
    printf("===========================================================\n");
    printf("%6s | %15s | %15s\n", "N", "D&C Multiplies", "Naive (N^3)");
    printf("-----------------------------------------------------------\n");
    
    FILE *fp = fopen("q5_data.csv", "w");
    if (fp) fprintf(fp, "N,DCMuls,NaiveMuls\n");

    for (int i = 0; i < NNS; i++) {
        int n = n_values[i];
        int **A = allocate_matrix(n);
        int **B = allocate_matrix(n);
        int **C_dc = allocate_matrix(n);
        int **C_nav = allocate_matrix(n);
        
        // Note: For actual special matrices, we would generate the pattern. 
        // Here we just track the recursive operation counts.
        dc_mults = 0;
        nav_mults = 0;
        
        multiply_special(A, B, C_dc, n);
        naive_multiply(A, B, C_nav, n);
        
        printf("%6d | %15lld | %15lld\n", n, dc_mults, nav_mults);
        if (fp) fprintf(fp, "%d,%lld,%lld\n", n, dc_mults, nav_mults);
        
        free_matrix(A, n); free_matrix(B, n); 
        free_matrix(C_dc, n); free_matrix(C_nav, n);
    }
    
    if (fp) fclose(fp);
    printf("\nData saved to q5_data.csv for plotting.\n");
    return 0;
}

int** allocate_matrix(int n) {
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) matrix[i] = (int *)calloc(n, sizeof(int));
    return matrix;
}

void free_matrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) free(matrix[i]);
    free(matrix);
}

void add_matrix(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) C[i][j] = A[i][j] + B[i][j];
}

void sub_matrix(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) C[i][j] = A[i][j] - B[i][j];
}

void naive_multiply(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
                nav_mults++;
            }
        }
    }
}

// Special O(n^2) D&C Multiplication
void multiply_special(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        dc_mults++; // Base case multiplication
        return;
    }
    
    int half = n / 2;
    int **A1 = allocate_matrix(half); int **A2 = allocate_matrix(half);
    int **B1 = allocate_matrix(half); int **B2 = allocate_matrix(half);
    
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            A1[i][j] = A[i][j]; A2[i][j] = A[i][j + half];
            B1[i][j] = B[i][j]; B2[i][j] = B[i][j + half];
        }
    }
    
    int **tempA = allocate_matrix(half); int **tempB = allocate_matrix(half);
    int **U = allocate_matrix(half);     int **V = allocate_matrix(half);
    
    add_matrix(A1, A2, tempA, half); add_matrix(B1, B2, tempB, half);
    multiply_special(tempA, tempB, U, half); // Recursion 1
    
    sub_matrix(A1, A2, tempA, half); sub_matrix(B1, B2, tempB, half);
    multiply_special(tempA, tempB, V, half); // Recursion 2
    
    int **C1 = allocate_matrix(half); int **C2 = allocate_matrix(half);
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C1[i][j] = (U[i][j] + V[i][j]) / 2;
            C2[i][j] = (U[i][j] - V[i][j]) / 2;
        }
    }
    
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j] = C1[i][j];                 C[i][j + half] = C2[i][j];          
            C[i + half][j] = C2[i][j];          C[i + half][j + half] = C1[i][j];   
        }
    }
    
    free_matrix(A1, half); free_matrix(A2, half); free_matrix(B1, half); free_matrix(B2, half);
    free_matrix(tempA, half); free_matrix(tempB, half); free_matrix(U, half); free_matrix(V, half);
    free_matrix(C1, half); free_matrix(C2, half);
}