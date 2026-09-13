#include <stdio.h>
#include <stdlib.h>

long long total_switch_moves = 0;

void turn_off(int n, int *switches);
void turn_on(int n, int *switches);
void toggle(int index, int *switches);
void get_data(int *n);
void display_summary(int n, long long moves);

int main(void) {
    int n;

    printf("Security Switches Problem\n");
    get_data(&n);

    int *switches = (int *)malloc(n * sizeof(int));
    if (switches == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Initialize all switches to ON (1) as specified
    for (int i = 0; i < n; i++) {
        switches[i] = 1;
    }

    printf("\nStarting toggle sequence (1-based index from right to left):\n");
    total_switch_moves = 0;
    turn_off(n, switches);

    display_summary(n, total_switch_moves);

    free(switches);
    return 0;
}

// Toggles switch at index (0-indexed from right)
void toggle(int index, int *switches) {
    switches[index] ^= 1;
    total_switch_moves++;
    printf("Move %lld: Toggled switch %d -> %s\n", 
           total_switch_moves, index + 1, switches[index] ? "ON" : "OFF");
}

// Turns off switches from 1 to n (where 1 is rightmost)
void turn_off(int n, int *switches) {
    if (n <= 0) return;

    if (n == 1) {
        if (switches[0] == 1) toggle(0, switches);
        return;
    }

    // Step 1: Turn off the first n - 2 switches
    turn_off(n - 2, switches);

    // Step 2: Toggle switch n (now switch n-1 is ON and 1..n-2 are OFF)
    if (switches[n - 1] == 1) toggle(n - 1, switches);

    // Step 3: Turn on the first n - 2 switches
    turn_on(n - 2, switches);

    // Step 4: Turn off all n - 1 switches
    turn_off(n - 1, switches);
}

// Turns on switches from 1 to n
void turn_on(int n, int *switches) {
    if (n <= 0) return;

    if (n == 1) {
        if (switches[0] == 0) toggle(0, switches);
        return;
    }

    // Step 1: Turn on the first n - 1 switches
    turn_on(n - 1, switches);

    // Step 2: Turn off the first n - 2 switches
    turn_off(n - 2, switches);

    // Step 3: Toggle switch n
    if (switches[n - 1] == 0) toggle(n - 1, switches);

    // Step 4: Turn on the first n - 2 switches
    turn_on(n - 2, switches);
}

void get_data(int *n) {
    printf("Enter number of switches (n): ");
    while (scanf("%d", n) != 1 || *n <= 0) {
        printf("Invalid input! Please enter a positive integer: ");
        while (getchar() != '\n');
    }
    printf("\n");
}

void display_summary(int n, long long moves) {
    printf("\n--- Security Switches Deactivation Summary ---\n");
    printf("Total Switches (n) : %d\n", n);
    printf("Total Moves Taken  : %lld\n", moves);
}