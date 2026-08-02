# Q2: Fair vs Biased Coin Simulation

## Objective
To simulate coin tosses using C and demonstrate that a fair coin yields a HEAD probability of approximately 0.5[cite: 1, 2]. The simulation is then extended to compare the results with a biased coin-tossing experiment[cite: 1, 2].

## Approach & Implementation Logic
The simulation relies on the standard `rand()` function from the `<stdlib.h>` library, seeded with `time(NULL)` to ensure randomness across different executions.

1. **Fair Coin Simulation:** To simulate a 50% probability, I used the modulo operator (`rand() % 2`). This strictly returns either 0 or 1, representing Tails and Heads, respectively.
2. **Biased Coin Simulation:** To simulate a specific bias (e.g., 70% probability of Heads), the random integer was normalized into a floating-point number between 0.0 and 1.0 by dividing by `RAND_MAX`. If this value falls below 0.70, it is counted as a Head.

The program runs these simulations over a large sample size (10,000 tosses) to apply the law of large numbers and calculate the experimental probability.

## Input & Output
* **Input:** The number of total tosses is internally set to 10,000.
* **Output:** The terminal prints the experimental probability of getting Heads for both the fair and biased coins. The fair coin output approaches 0.50, while the biased coin approaches the set threshold of 0.70.