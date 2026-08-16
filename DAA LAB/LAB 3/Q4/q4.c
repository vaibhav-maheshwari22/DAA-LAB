#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NNS 6

long long str_mults = 0, str_adds = 0;
long long nav_mults = 0, nav_adds = 0;

static int n_values[NNS] = {2, 4, 8, 16, 32, 64}; // Limit to 64 to avoid high memory overhead

int** allocate_matrix(int n);
void free_matrix(int **matrix, int n);
void add(int **A, int **B, int **C, int n);
void sub(int **A, int **B, int **C, int n);
void strassen(int **A, int **B, int **C, int n);
void naive_multiply(int **A, int **B, int **C, int n);
void run_test(int idx);

int main() {
    srand(time(NULL));
    
    printf("\n===========================================================\n");
    printf(" STRASSEN'S D&C MULTIPLICATION vs NAIVE TRIPLE LOOP\n");
    printf("===========================================================\n");
    printf("%6s | %13s | %13s | %13s\n", "N", "Strassen Muls", "Naive Muls", "Theoretical");
    printf("-----------------------------------------------------------\n");
    
    FILE *fp = fopen("q4_data.csv", "w");
    if (fp) fprintf(fp, "N,StrassenMuls,NaiveMuls\n");

    for (int i = 0; i < NNS; i++) {
        run_test(i);
        
        // Strassen should exactly match 7^(log2(N)) multiplications
        long long expected_strassen = (long long)pow(7, log2(n_values[i]));
        
        printf("%6d | %13lld | %13lld | %13lld\n", 
               n_values[i], str_mults, nav_mults, expected_strassen);
               
        if (fp) fprintf(fp, "%d,%lld,%lld\n", n_values[i], str_mults, nav_mults);
    }
    
    if (fp) fclose(fp);
    
    printf("\nComplexity Proof:\n");
    printf("Naive uses exactly N^3 multiplications.\n");
    printf("Strassen uses 7 multiplications per recursion -> O(N^log2(7)) -> O(N^2.81)\n");
    printf("Note: Memory overhead in Strassen is high, making it practical only for large N.\n\n");

    return 0;
}

int** allocate_matrix(int n) {
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)calloc(n, sizeof(int));
    }
    return matrix;
}

void free_matrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) free(matrix[i]);
    free(matrix);
}

void add(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
            str_adds++; // Track additions
        }
}

void sub(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
            str_adds++; // Track additions
        }
}

void naive_multiply(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
                nav_mults++;
                nav_adds++;
            }
        }
    }
}

void strassen(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        str_mults++; // Track base case multiplications
        return;
    }
    
    int new_n = n / 2;
    
    // Allocate sub-matrices
    int **A11 = allocate_matrix(new_n), **A12 = allocate_matrix(new_n);
    int **A21 = allocate_matrix(new_n), **A22 = allocate_matrix(new_n);
    int **B11 = allocate_matrix(new_n), **B12 = allocate_matrix(new_n);
    int **B21 = allocate_matrix(new_n), **B22 = allocate_matrix(new_n);
    
    int **C11 = allocate_matrix(new_n), **C12 = allocate_matrix(new_n);
    int **C21 = allocate_matrix(new_n), **C22 = allocate_matrix(new_n);
    
    int **M1 = allocate_matrix(new_n), **M2 = allocate_matrix(new_n);
    int **M3 = allocate_matrix(new_n), **M4 = allocate_matrix(new_n);
    int **M5 = allocate_matrix(new_n), **M6 = allocate_matrix(new_n);
    int **M7 = allocate_matrix(new_n);
    
    int **temp1 = allocate_matrix(new_n), **temp2 = allocate_matrix(new_n);
    
    // Divide matrices into 4 halves
    for (int i = 0; i < new_n; i++) {
        for (int j = 0; j < new_n; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + new_n];
            A21[i][j] = A[i + new_n][j];
            A22[i][j] = A[i + new_n][j + new_n];
            
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + new_n];
            B21[i][j] = B[i + new_n][j];
            B22[i][j] = B[i + new_n][j + new_n];
        }
    }
    
    // Calculate M1 to M7
    add(A11, A22, temp1, new_n); add(B11, B22, temp2, new_n); strassen(temp1, temp2, M1, new_n); 
    add(A21, A22, temp1, new_n); strassen(temp1, B11, M2, new_n); 
    sub(B12, B22, temp2, new_n); strassen(A11, temp2, M3, new_n); 
    sub(B21, B11, temp2, new_n); strassen(A22, temp2, M4, new_n); 
    add(A11, A12, temp1, new_n); strassen(temp1, B22, M5, new_n); 
    sub(A21, A11, temp1, new_n); add(B11, B12, temp2, new_n); strassen(temp1, temp2, M6, new_n); 
    sub(A12, A22, temp1, new_n); add(B21, B22, temp2, new_n); strassen(temp1, temp2, M7, new_n); 
    
    // Calculate C sub-matrices
    add(M1, M4, temp1, new_n); sub(temp1, M5, temp2, new_n); add(temp2, M7, C11, new_n); 
    add(M3, M5, C12, new_n); 
    add(M2, M4, C21, new_n); 
    sub(M1, M2, temp1, new_n); add(temp1, M3, temp2, new_n); add(temp2, M6, C22, new_n); 
    
    // Combine C sub-matrices into C
    for (int i = 0; i < new_n; i++) {
        for (int j = 0; j < new_n; j++) {
            C[i][j] = C11[i][j];
            C[i][j + new_n] = C12[i][j];
            C[i + new_n][j] = C21[i][j];
            C[i + new_n][j + new_n] = C22[i][j];
        }
    }
    
    // Free all memory
    free_matrix(A11, new_n); free_matrix(A12, new_n); free_matrix(A21, new_n); free_matrix(A22, new_n);
    free_matrix(B11, new_n); free_matrix(B12, new_n); free_matrix(B21, new_n); free_matrix(B22, new_n);
    free_matrix(C11, new_n); free_matrix(C12, new_n); free_matrix(C21, new_n); free_matrix(C22, new_n);
    free_matrix(M1, new_n); free_matrix(M2, new_n); free_matrix(M3, new_n); free_matrix(M4, new_n);
    free_matrix(M5, new_n); free_matrix(M6, new_n); free_matrix(M7, new_n);
    free_matrix(temp1, new_n); free_matrix(temp2, new_n);
}

void run_test(int idx) {
    int n = n_values[idx];
    
    int **A = allocate_matrix(n);
    int **B = allocate_matrix(n);
    int **C_str = allocate_matrix(n);
    int **C_nav = allocate_matrix(n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }
    
    // Reset global counters
    str_mults = 0; str_adds = 0;
    nav_mults = 0; nav_adds = 0;
    
    strassen(A, B, C_str, n);
    naive_multiply(A, B, C_nav, n);
    
    // Validation
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (C_str[i][j] != C_nav[i][j]) {
                printf("Error: Mismatch at size %d!\n", n);
                exit(1);
            }
        }
    }
    
    free_matrix(A, n); free_matrix(B, n); 
    free_matrix(C_str, n); free_matrix(C_nav, n);
}