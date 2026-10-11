#include <stdio.h>
#include <stdlib.h>
#include <float.h>

int main(void) {
    int n;
    double W;

    printf("Enter n and capacity W: ");
    if (scanf("%d %lf", &n, &W) != 2 || n < 1 || n > 20 || W < 0.0) {
        printf("Invalid input (need 1 <= n <= 20, W >= 0).\n");
        return 1;
    }

    double v[20], w[20], lam[20];
    printf("Enter v_i w_i lambda_i for each item:\n");
    for (int i = 0; i < n; i++) {
        if (scanf("%lf %lf %lf", &v[i], &w[i], &lam[i]) != 3 ||
            w[i] <= 0.0 || lam[i] < 0.0) {
            printf("Invalid item data.\n");
            return 1;
        }
    }

    // Total number of subsets of the n items
    int states = 1 << n;

    // dp[mask]  = best value using exactly the items in mask (all fully eaten)
    // wt[mask]  = total weight of items in mask (= current time t)
    // par[mask] = previous mask, for reconstruction
    // pk[mask]  = index of last item added to reach this mask
    double *dp  = malloc(states * sizeof(double));
    double *wt  = calloc(states, sizeof(double));
    int    *par = malloc(states * sizeof(int));
    int    *pk  = malloc(states * sizeof(int));

    if (!dp || !wt || !par || !pk) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int m = 0; m < states; m++) {
        dp[m]  = -DBL_MAX;
        par[m] = -1;
        pk[m]  = -1;
    }
    dp[0] = 0.0;

    int    bestMask   = 0;
    double best       = 0.0;
    int    last       = -1;    // index of fractional item, or -1
    double lastAmount = 0.0;

    for (int m = 0; m < states; m++) {
        if (dp[m] == -DBL_MAX) continue;

        double t = wt[m];      // current time

        // Option A: stop here with mask fully consumed
        if (dp[m] > best) {
            best = dp[m];
            bestMask = m;
            last = -1;
            lastAmount = 0.0;
        }

        for (int j = 0; j < n; j++) {
            if (m & (1 << j)) continue;       // item already used

            double remaining = W - t;
            if (remaining <= 0.0) continue;

            // Option B: consume a fraction of item j as the last item.
            // Value = integral of density from t to t + amt.
            double amt = (w[j] < remaining) ? w[j] : remaining;
            double gain = (v[j] / w[j]) * amt
                        - lam[j] * (t * amt + amt * amt / 2.0);

            if (dp[m] + gain > best) {
                best = dp[m] + gain;
                bestMask = m;
                last = j;
                lastAmount = amt;
            }

            // Option C: consume item j fully and extend the mask
            if (t + w[j] <= W) {
                int next = m | (1 << j);
                double gainFull = v[j]
                                - lam[j] * (t * w[j] + w[j] * w[j] / 2.0);

                if (dp[m] + gainFull > dp[next]) {
                    dp[next]  = dp[m] + gainFull;
                    par[next] = m;
                    pk[next]  = j;
                    wt[next]  = t + w[j];
                }
            }
        }
    }

    // Reconstruct the fully consumed items in reverse order
    int ord[20], cnt = 0;
    int cur = bestMask;
    while (cur != 0) {
        ord[cnt++] = pk[cur];
        cur = par[cur];
    }

    printf("\nMaximum value: %.6f\n", best);
    printf("Schedule (item index, weight consumed):\n");

    for (int i = cnt - 1; i >= 0; i--) {
        int item = ord[i];
        printf("  item %d : %.6f\n", item + 1, w[item]);
    }

    if (last >= 0) {
        printf("  item %d : %.6f  (fractional)\n", last + 1, lastAmount);
    }

    free(dp);
    free(wt);
    free(par);
    free(pk);
    return 0;
}