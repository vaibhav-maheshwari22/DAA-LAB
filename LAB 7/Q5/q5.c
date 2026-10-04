#include <stdio.h>
#include <stdlib.h>

void hit_moving_target(int n);
void get_data(int *n);

int main(void) {
    int n;
    printf("Hitting a Moving Target Problem\n");
    get_data(&n);
    hit_moving_target(n);
    return 0;
}

void hit_moving_target(int n) {
    if (n <= 1) {
        printf("Trivial case: 1 spot available. Shoot spot 1 directly.\n");
        return;
    }
    if (n == 2) {
        printf("\nShooting sequence: Spot 2, Spot 2\nGuaranteed hit in 2 shots.\n");
        return;
    }

    printf("\nDeterministic Universal Shooting Plan:\n");
    int shot_count = 1;

    // Phase 1: Forward sweep
    printf("Phase 1: Forward Sweep \n");
    for (int spot = 2; spot <= n - 1; spot++) {
        printf("Shot %d -> Spot %d\n", shot_count++, spot);
    }

    // Phase 2: Backward sweep 
    printf("Phase 2: Backward Sweep\n");
    for (int spot = n - 1; spot >= 2; spot--) {
        printf("Shot %d -> Spot %d\n", shot_count++, spot);
    }

    printf("\nTarget is guaranteed to be hit within %d shots.\n", shot_count - 1);
}

void get_data(int *n) {
    printf("Enter number of hiding spots along the straight line (n > 1): ");
    while (scanf("%d", n) != 1 || *n <= 1) {
        printf("Invalid input! Enter an integer greater than 1: ");
        while (getchar() != '\n');
    }
    printf("\n");
}