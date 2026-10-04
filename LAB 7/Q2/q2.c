#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int solve_egg_drop(int eggs, int floors);
void get_data(int *eggs, int *floors);
void display_results(int eggs, int floors, int min_drops);

int main(void) {
    int eggs, floors;

    printf("Super Egg Testing Experiment (DP)\n");
    get_data(&eggs, &floors);

    int min_drops = solve_egg_drop(eggs, floors);

    display_results(eggs, floors, min_drops);

    return 0;
}

// DP tabulation to compute minimum drops 
int solve_egg_drop(int eggs, int floors) {
    
    // dp[i][j] stores min drops needed for i eggs and j floors
    int **dp = (int **)malloc((eggs + 1) * sizeof(int *));

    if (dp == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    for (int i = 0; i <= eggs; i++) {
        dp[i] = (int *)malloc((floors + 1) * sizeof(int));
        if (dp[i] == NULL) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
    }

    // Base cases:
    // 1 egg needs linear search (f drops for f floors)
    for (int j = 1; j <= floors; j++) {
        dp[1][j] = j;
    }
    // 0 floors need 0 drops, 1 floor needs 1 drop
    for (int i = 1; i <= eggs; i++) {
        dp[i][0] = 0;
        dp[i][1] = 1;
    }

    // Fill the rest of the table
    for (int i = 2; i <= eggs; i++) {
        for (int j = 2; j <= floors; j++) {
            dp[i][j] = INT_MAX;
            for (int k = 1; k <= j; k++) {
                int broken = dp[i - 1][k - 1];
                int unbroken = dp[i][j - k];
                int worst = 1 + (broken > unbroken ? broken : unbroken);

                if (worst < dp[i][j]) {
                    dp[i][j] = worst;
                }
            }
        }
    }

    int result = dp[eggs][floors];

    // Clean up allocated memory
    for (int i = 0; i <= eggs; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

void get_data(int *eggs, int *floors) {
    printf("Enter number of eggs (E): ");
    while (scanf("%d", eggs) != 1 || *eggs <= 0) {
        printf("Invalid input! Please enter a positive integer for eggs: ");
        while (getchar() != '\n');
    }

    printf("Enter number of floors (F): ");
    while (scanf("%d", floors) != 1 || *floors <= 0) {
        printf("Invalid input! Please enter a positive integer for floors: ");
        while (getchar() != '\n');
    }
    printf("\n");
}

void display_results(int eggs, int floors, int min_drops) {
    printf("--- Test Experiment Analysis ---\n");
    printf("Number of Eggs   : %d\n", eggs);
    printf("Number of Floors : %d\n", floors);
    printf("Minimum Drops    : %d\n", min_drops);
}