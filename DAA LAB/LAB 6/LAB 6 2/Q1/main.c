#include <stdio.h>

/* Time Complexity: O(N) | Space Complexity: O(N) */
int main(void) {
    int n;
    printf("Enter n to find the nth Fibonacci number: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Invalid input\n");
        return 1;
    }

    long long fibonacci[n + 2]; // +2 to handle n=0 safely
    fibonacci[0] = 0;
    fibonacci[1] = 1;

    for (int i = 2; i <= n; i++) {
        fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
    }

    printf("Fibonacci(%d) = %lld\n", n, fibonacci[n]);
    return 0;
}