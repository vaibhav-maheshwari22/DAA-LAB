/*
 * Description: 2D square matrix operations and their worst-case complexities.
 * 
 * Complexity Analysis:
 * (i)   Addition: O(n^2) - Iterates through all n x n elements.
 * (ii)  Multiplication: O(n^3) - Standard 3 nested loops.
 * (iii) Zero Matrix Check: O(n^2) - Linear scan of the 2D grid.
 * (iv)  Symmetric Check: O(n^2) - Scans the upper triangle to compare with lower.
 * (v)   Determinant: O(n^3) - Uses Gaussian elimination (Upper Triangular conversion).
 * (vi)  Transpose in situ: O(n^2) - Swaps n(n-1)/2 elements in place.
 * (vii) Eigenvalue/Vector: O(k * n^2) - Power iteration method for 'k' iterations.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

// Utility function to print matrix
void print_matrix(int n, double mat[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.2f ", mat[i][j]);
        }
        printf("\n");
    }
}

// (i) Matrix Addition
void add_matrices(int n, double A[n][n], double B[n][n], double C[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// (ii) Matrix Multiplication
void multiply_matrices(int n, double A[n][n], double B[n][n], double C[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// (iii) Zero Matrix Check
bool is_zero_matrix(int n, double mat[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fabs(mat[i][j]) > 1e-9) return false;
        }
    }
    return true;
}

// (iv) Symmetric Matrix Check
bool is_symmetric(int n, double mat[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (fabs(mat[i][j] - mat[j][i]) > 1e-9) return false;
        }
    }
    return true;
}

// (v) Determinant (using Gaussian Elimination)
double determinant(int n, double mat[n][n]) {
    double temp[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            temp[i][j] = mat[i][j];
            
    double det = 1.0;
    for (int i = 0; i < n; i++) {
        if (fabs(temp[i][i]) < 1e-9) return 0.0; // Singular matrix
        
        for (int j = i + 1; j < n; j++) {
            double ratio = temp[j][i] / temp[i][i];
            for (int k = i; k < n; k++) {
                temp[j][k] -= ratio * temp[i][k];
            }
        }
        det *= temp[i][i];
    }
    return det;
}

// (vi) Transpose in-situ
void transpose_in_situ(int n, double mat[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double temp = mat[i][j];
            mat[i][j] = mat[j][i];
            mat[j][i] = temp;
        }
    }
}

// (vii) Dominant Eigenvalue & Eigenvector (Power Iteration)
double power_iteration(int n, double A[n][n], double *eigenvector) {
    double v[n], w[n];
    for (int i = 0; i < n; i++) v[i] = 1.0; // Initial guess
    
    double eigenvalue = 0.0;
    int iterations = 1000;
    
    for (int iter = 0; iter < iterations; iter++) {
        double norm = 0.0;
        for (int i = 0; i < n; i++) {
            w[i] = 0.0;
            for (int j = 0; j < n; j++) w[i] += A[i][j] * v[j];
            norm += w[i] * w[i];
        }
        norm = sqrt(norm);
        for (int i = 0; i < n; i++) v[i] = w[i] / norm;
    }
    
    // Rayleigh quotient to find eigenvalue
    double numerator = 0.0, denominator = 0.0;
    for (int i = 0; i < n; i++) {
        double Av_i = 0.0;
        for (int j = 0; j < n; j++) Av_i += A[i][j] * v[j];
        numerator += v[i] * Av_i;
        denominator += v[i] * v[i];
    }
    
    for (int i = 0; i < n; i++) eigenvector[i] = v[i];
    return numerator / denominator;
}

int main() {
    int n;
    printf("2D Square Matrix Operations\n---------------------------\n");
    printf("Enter matrix dimension (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    double A[n][n], B[n][n], C[n][n];

    printf("\nEnter elements of Matrix A (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%lf", &A[i][j]);

    printf("\nEnter elements of Matrix B (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%lf", &B[i][j]);

    // (i) Addition
    add_matrices(n, A, B, C);
    printf("\n(i) Matrix Addition (A + B):\n");
    print_matrix(n, C);

    // (ii) Multiplication
    multiply_matrices(n, A, B, C);
    printf("\n(ii) Matrix Multiplication (A * B):\n");
    print_matrix(n, C);

    // (iii) Zero Check (checking Matrix A)
    printf("\n(iii) Is Matrix A a Zero Matrix? %s\n", is_zero_matrix(n, A) ? "Yes" : "No");

    // (iv) Symmetric Check (checking Matrix A)
    printf("(iv) Is Matrix A Symmetric? %s\n", is_symmetric(n, A) ? "Yes" : "No");

    // (v) Determinant (of Matrix A)
    printf("(v) Determinant of Matrix A: %.2f\n", determinant(n, A));

    // (vi) Transpose in-situ (applying to Matrix A)
    transpose_in_situ(n, A);
    printf("\n(vi) Matrix A Transposed in-situ:\n");
    print_matrix(n, A);

    // (vii) Eigenvalue / Eigenvector (calculating for original Matrix B)
    double eigenvector[n];
    double eigenvalue = power_iteration(n, B, eigenvector);
    printf("\n(vii) Dominant Eigenvalue of Matrix B: %.4f\n", eigenvalue);
    printf("      Corresponding Eigenvector: [ ");
    for (int i = 0; i < n; i++) printf("%.4f ", eigenvector[i]);
    printf("]\n");

    return 0;
}