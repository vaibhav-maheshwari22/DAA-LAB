#include <stdio.h>
#include <stdlib.h>

long long calculate_total_coins(int n);
long long calculate_min_moves(int n);
void get_data(int *n);
void display_results(int n, long long total_coins, long long min_moves);

int main(void) {
    int n;
    printf("Invert the Coin-Triangle Problem\n");
    get_data(&n);

    // Compute mathematical metrics
    long long total_coins = calculate_total_coins(n);
    long long min_moves = calculate_min_moves(n);

    display_results(n, total_coins, min_moves);

    return 0;
}

// Computes total coins in an equilateral triangular lattice of side n
long long calculate_total_coins(int n) {
    return ((long long)n * (n + 1)) / 2;
}

// formula for minimum coin sliding relocations
long long calculate_min_moves(int n) {
    if (n <= 0) return 0;
    return ((long long)n * (n + 1)) / 6;
}

// Read input 
void get_data(int *n) {
    printf("Enter number of rows in the coin triangle (e.g., 4): ");
    while (scanf("%d", n) != 1 || *n <= 0) {
        printf("Invalid input! Please enter a positive integer: ");
        // Flush invalid characters from stdin buffer
        while (getchar() != '\n');
    }
    printf("\n");
}

// display
void display_results(int n, long long total_coins, long long min_moves) {
    long long preserved_coins = total_coins - min_moves;

    printf("--- Coin-Triangle Inversion Analysis ---\n");
    printf("Number of Rows (n)         : %d\n", n);
    printf("Total Coins (T_n)          : %lld\n", total_coins);
    printf("Overlapping Preserved Coins: %lld\n", preserved_coins);
    printf("Minimum Moves Required     : %lld\n", min_moves);
    
}