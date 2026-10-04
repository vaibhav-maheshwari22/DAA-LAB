#include <stdio.h>
#include <math.h>

int main() {

    // Open file 
    FILE *fp = fopen("q1_data.csv", "w");

    if (fp == NULL) return 1;

    // Write CSV headers 
    fprintf(fp, "n,log2n,12sqrtn,50sqrtn,n051,nlog2n,n2_minus324,100n2_6n,2n3,nlog2n_pow,pow3n\n");

    // Generate data points
    for (double n = 1; n <= 40; n++) {

        double f_log2n = log2(n);
        double f_12sqrtn = 12 * sqrt(n);
        double f_50sqrtn = 50 * pow(n, 0.5);
        double f_n051 = pow(n, 0.51);
        double f_nlog2n = n * log2(n);
        double f_n2_minus324 = pow(n, 2) - 324;
        double f_100n2_6n = 100 * pow(n, 2) + 6 * n;
        double f_2n3 = 2 * pow(n, 3);
        double f_nlog2n_pow = pow(n, log2(n));
        double f_pow3n = pow(3, n);

        // Append calculated values 
        fprintf(fp, "%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n", 
                n, f_log2n, f_12sqrtn, f_50sqrtn, f_n051, f_nlog2n, 
                f_n2_minus324, f_100n2_6n, f_2n3, f_nlog2n_pow, f_pow3n);
    }
    
    fclose(fp);
    printf("Data successfully written to q1_data.csv\n");

    return 0;
}
