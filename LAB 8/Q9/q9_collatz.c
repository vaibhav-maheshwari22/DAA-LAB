/*
 DAA Lab 08 - Q9: Collatz Conjecture Analysis (3n + 1)

 Rules:
   T(n) = n/2       if n is even
   T(n) = 3n + 1    if n is odd
   Stop when n = 1.

 Features:
   - Single value trajectory (with dynamically resized buffer)
   - Interval [a, b] analysis
   - 64-bit integers to prevent overflow
   - Modular functions + menu-driven main

 Time Complexity:
   For single n, O(L(n)) where L(n) = trajectory length.
   For interval, O(sum of L(k)) for k in [a, b].
   (L(n) has no proven closed form — Collatz is open.)

 Space Complexity:
   Single trajectory: O(L(n)) on heap.
   Interval: O(max L(k)) since buffer freed after each number.
*/

#include <stdio.h>
#include <stdlib.h>

// Next Collatz number
unsigned long long getNextCollatz(unsigned long long n) {
    if (n % 2 == 0)
        return n / 2;
    else
        return (3ULL * n) + 1ULL;
}

// Build trajectory using dynamic memory (malloc + realloc)
unsigned long long* computeTrajectory(unsigned long long n, int *out_steps, unsigned long long *out_peak) {
    int capacity = 64;
    int count = 0;

    unsigned long long *trajectory = (unsigned long long *)malloc(capacity * sizeof(unsigned long long));
    if (trajectory == NULL) {
        printf("Memory allocation failed!\n");
        *out_steps = 0;
        *out_peak = n;
        return NULL;
    }

    unsigned long long curr = n;
    unsigned long long peak = n;
    trajectory[count++] = curr;

    while (curr != 1ULL) {
        curr = getNextCollatz(curr);

        if (curr > peak) peak = curr;

        // Grow buffer if needed
        if (count >= capacity) {
            capacity *= 2;
            unsigned long long *temp = (unsigned long long *)realloc(trajectory, capacity * sizeof(unsigned long long));
            if (temp == NULL) {
                printf("Memory reallocation failed!\n");
                free(trajectory);
                *out_steps = 0;
                *out_peak = peak;
                return NULL;
            }
            trajectory = temp;
        }

        trajectory[count++] = curr;
    }

    *out_steps = count;
    *out_peak = peak;
    return trajectory;
}

// Analyze a single starting value
void analyzeSingleValue(unsigned long long n) {
    if (n < 1ULL) {
        printf("Starting number must be >= 1.\n");
        return;
    }

    printf("\n----------------------------------------------------\n");
    printf("   Collatz Analysis for Starting Value n = %llu\n", n);
    printf("----------------------------------------------------\n");

    int steps = 0;
    unsigned long long peak = 0;
    unsigned long long *trajectory = computeTrajectory(n, &steps, &peak);

    if (trajectory == NULL) return;

    printf("Total trajectory points (including start): %d\n", steps);
    printf("Total step transitions to reach 1: %d\n", steps - 1);
    printf("Peak (maximum value reached): %llu\n", peak);

    printf("\nTrajectory Path:\n");
    for (int i = 0; i < steps; i++) {
        printf("%llu", trajectory[i]);
        if (i < steps - 1) printf(" -> ");
        if ((i + 1) % 8 == 0 && i < steps - 1) printf("\n   ");
    }
    printf("\n----------------------------------------------------\n");

    free(trajectory);
}

// Analyze interval [a, b]
void analyzeInterval(unsigned long long a, unsigned long long b) {
    if (a > b || a < 1ULL) {
        printf("Invalid interval range. Ensure 1 <= a <= b.\n");
        return;
    }

    printf("\n----------------------------------------------------\n");
    printf("   Collatz Analysis for Interval [%llu, %llu]\n", a, b);
    printf("----------------------------------------------------\n");

    int max_length = 0;
    unsigned long long number_with_max_length = a;
    unsigned long long global_highest_peak = 0;
    unsigned long long number_with_highest_peak = a;

    printf("%-12s %-15s %-20s\n", "Number (n)", "Steps to 1", "Peak Value");
    printf("----------------------------------------------------\n");

    for (unsigned long long k = a; k <= b; k++) {
        int steps = 0;
        unsigned long long peak = 0;
        unsigned long long *trajectory = computeTrajectory(k, &steps, &peak);

        if (trajectory != NULL) {
            int transitions = steps - 1;

            // Print row only if interval is small enough
            if ((b - a + 1) <= 50) {
                printf("%-12llu %-15d %-20llu\n", k, transitions, peak);
            }

            if (transitions > max_length) {
                max_length = transitions;
                number_with_max_length = k;
            }

            if (peak > global_highest_peak) {
                global_highest_peak = peak;
                number_with_highest_peak = k;
            }

            free(trajectory);
        }
    }

    printf("----------------------------------------------------\n");
    printf("INTERVAL SUMMARY RESULTS:\n");
    printf("  Maximum Trajectory Length (transitions): %d (achieved by n = %llu)\n",
           max_length, number_with_max_length);
    printf("  Highest Peak Value Reached: %llu (achieved by n = %llu)\n",
           global_highest_peak, number_with_highest_peak);
    printf("----------------------------------------------------\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n====================================================\n");
        printf("     Collatz Conjecture (3n + 1) Modular System    \n");
        printf("====================================================\n");
        printf("1. Analyze single starting value n\n");
        printf("2. Analyze an interval [a, b]\n");
        printf("3. Exit\n");
        printf("Enter your choice (1-3): ");

        if (scanf("%d", &choice) != 1) {
            printf("Exiting program.\n");
            break;
        }

        if (choice == 1) {
            unsigned long long n;
            printf("Enter starting integer n (n >= 1): ");
            if (scanf("%llu", &n) == 1) {
                analyzeSingleValue(n);
            }
        } else if (choice == 2) {
            unsigned long long a, b;
            printf("Enter lower bound a: ");
            scanf("%llu", &a);
            printf("Enter upper bound b: ");
            scanf("%llu", &b);
            analyzeInterval(a, b);
        } else if (choice == 3) {
            printf("Exiting Collatz Conjecture Program. Goodbye!\n");
            break;
        } else {
            printf("Invalid choice! Please choose 1, 2, or 3.\n");
        }
    }

    return 0;
}