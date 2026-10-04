#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long total_moves = 0;

void standard_hanoi(int n, char from, char to, char aux);
void reve_hanoi(int n, char from, char to, char aux1, char aux2);
void get_data(int *n);
void display_summary(int n, long long moves);

int main(void) {
    int n;

    printf("Reve's Puzzle (4 Pegs)\n");
    get_data(&n);

    total_moves = 0;
    reve_hanoi(n, 'A', 'D', 'B', 'C');

    display_summary(n, total_moves);

    return 0;
}

// Classical 3-peg Hanoi subroutine for the bottom (n - k) disks
void standard_hanoi(int n, char from, char to, char aux) {
    if (n <= 0) return;

    standard_hanoi(n - 1, from, aux, to);
    printf("Move disk %d from %c -> %c\n", n, from, to);
    total_moves++;
    standard_hanoi(n - 1, aux, to, from);
}

// 4-peg Frame-Stewart algorithm
void reve_hanoi(int n, char from, char to, char aux1, char aux2) {
    if (n <= 0) return;

    if (n == 1) {
        printf("Move disk 1 from %c -> %c\n", from, to);
        total_moves++;
        return;
    }

    // Optimal partition parameter k for Frame-Stewart strategy
    int k = n - (int)round(sqrt(2 * n + 1)) + 1;
    if (k < 1) k = 1;

    // Step 1: Move top k disks to aux1 using 4 pegs
    reve_hanoi(k, from, aux1, aux2, to);

    // Step 2: Move remaining n - k larger disks to 'to' using 3 pegs
    standard_hanoi(n - k, from, to, aux2);

    // Step 3: Move k disks from aux1 to 'to' using 4 pegs
    reve_hanoi(k, aux1, to, from, aux2);
}

void get_data(int *n) {
    printf("Enter number of disks (n=8 for 33 moves target): ");
    while (scanf("%d", n) != 1 || *n <= 0) {
        printf("Invalid input! Please enter a positive integer: ");
        while (getchar() != '\n');
    }
    printf("\n");
}

void display_summary(int n, long long moves) {
    printf("\nMove Execution Summary\n");
    printf("Total Disks (n)  : %d\n", n);
    printf("Total Moves Taken: %lld\n", moves);
}