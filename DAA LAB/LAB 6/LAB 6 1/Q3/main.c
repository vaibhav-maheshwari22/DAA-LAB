/*
 * Description: O(n log n) Divide and Conquer algorithm for vector convolution
 * using the Fast Fourier Transform (FFT).
 * 
 * Complexity Analysis:
 * - Padding arrays to next power of 2: O(N)
 * - FFT of Vector A: O(N log N)
 * - FFT of Vector B: O(N log N)
 * - Point-wise Multiplication: O(N)
 * - Inverse FFT of Result: O(N log N)
 * Overall Time Complexity: O(N log N), where N is the padded size (N >= m + n - 1).
 * Overall Space Complexity: O(N) for dynamically allocated complex arrays.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Recursive Fast Fourier Transform (Divide & Conquer)
void fft(double complex *a, int n, int invert) {
    if (n == 1) return;

    double complex *a0 = (double complex *)malloc((n / 2) * sizeof(double complex));
    double complex *a1 = (double complex *)malloc((n / 2) * sizeof(double complex));
    
    // Divide into even and odd indices
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }

    // Conquer
    fft(a0, n / 2, invert);
    fft(a1, n / 2, invert);

    // Combine
    double angle = 2 * M_PI / n * (invert ? -1 : 1);
    double complex w = 1;
    double complex wn = cos(angle) + I * sin(angle);

    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        
        // Scale down during inverse FFT
        if (invert) {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
        w *= wn;
    }

    free(a0);
    free(a1);
}

// Helper to find the next power of 2
int next_power_of_2(int val) {
    int power = 1;
    while (power < val) {
        power *= 2;
    }
    return power;
}

int main() {
    int m, n;
    
    printf("O(n log n) Vector Convolution (FFT)\n");
    printf("-----------------------------------\n");
    
    printf("Enter size of Vector A (m): ");
    if (scanf("%d", &m) != 1 || m <= 0) return 1;
    
    printf("Enter size of Vector B (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    // Convolution size is m + n - 1. FFT requires size to be a power of 2.
    int result_size = m + n - 1;
    int N = next_power_of_2(result_size);

    // Allocate memory and initialize to 0
    double complex *A = (double complex *)calloc(N, sizeof(double complex));
    double complex *B = (double complex *)calloc(N, sizeof(double complex));

    printf("\nEnter %d elements for Vector A:\n", m);
    for (int i = 0; i < m; i++) {
        double val;
        scanf("%lf", &val);
        A[i] = val + 0 * I;
    }

    printf("\nEnter %d elements for Vector B:\n", n);
    for (int i = 0; i < n; i++) {
        double val;
        scanf("%lf", &val);
        B[i] = val + 0 * I;
    }

    // Step 1: Compute FFT of both vectors
    fft(A, N, 0);
    fft(B, N, 0);

    // Step 2: Point-wise multiplication in frequency domain
    double complex *C = (double complex *)calloc(N, sizeof(double complex));
    for (int i = 0; i < N; i++) {
        C[i] = A[i] * B[i];
    }

    // Step 3: Compute Inverse FFT to convert back to time domain
    fft(C, N, 1);

    // Print the valid convolution elements
    printf("\nConvolution Result C (size %d):\n", result_size);
    for (int i = 0; i < result_size; i++) {
        printf("C[%d] = %.2f\n", i, creal(C[i]));
    }

    // Free memory
    free(A);
    free(B);
    free(C);
    
    return 0;
}