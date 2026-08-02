#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    int total_tosses = 10000;
    int fair_heads = 0;
    int biased_heads = 0;
    
    // Seed the random number generator with current time
    srand(time(NULL)); 

    // Simulate coin tosses
    for(int i = 0; i < total_tosses; i++) {
        
        // Fair coin
        if (rand() % 2 == 1) {
            fair_heads++;
        }
        
        // Biased coin
        if ((float)rand() / RAND_MAX < 0.70) {
            biased_heads++;
        }
    }

    printf("Total Tosses: %d\n", total_tosses);
    printf("Fair Coin Heads Probability: %f\n", (float)fair_heads / total_tosses);
    printf("Biased Coin Heads Probability: %f\n", (float)biased_heads / total_tosses);

    return 0;
}
