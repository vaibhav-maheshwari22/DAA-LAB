#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n, i;
    int *rating, *left, *right;
    long long total = 0;

    if (scanf("%d", &n) != 1 || n < 1) {
        fprintf(stderr, "Invalid child count.\n");
        return 1;
    }

    rating = malloc((size_t)n * sizeof(*rating));
    left   = malloc((size_t)n * sizeof(*left));
    right  = malloc((size_t)n * sizeof(*right));

    if (!rating || !left || !right) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(rating); free(left); free(right);
        return 1;
    }

    for (i = 0; i < n; i++) {
        if (scanf("%d", &rating[i]) != 1) {
            fprintf(stderr, "Invalid rating input.\n");
            free(rating); free(left); free(right);
            return 1;
        }
    }

    // Left-to-right pass: if rating is higher than the left neighbour,
    // this child must get at least (left neighbour + 1) candies.
    left[0] = 1;
    for (i = 1; i < n; i++)
        left[i] = (rating[i] > rating[i - 1]) ? left[i - 1] + 1 : 1;

    // Right-to-left pass: same but comparing to the right neighbour.
    right[n - 1] = 1;
    for (i = n - 2; i >= 0; i--)
        right[i] = (rating[i] > rating[i + 1]) ? right[i + 1] + 1 : 1;

    // Take the larger of the two directional requirements at each index.
    printf("Candies:");
    for (i = 0; i < n; i++) {
        int candies = (left[i] > right[i]) ? left[i] : right[i];
        total += candies;
        printf(" %d", candies);
    }
    printf("\nMinimum candies: %lld\n", total);

    free(rating); free(left); free(right);
    return 0;
}