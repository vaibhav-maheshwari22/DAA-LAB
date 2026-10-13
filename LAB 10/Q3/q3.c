/*
 * Input: V E K, V vertex weights, then E arriving edges u v (vertices 0..V-1).
 * Time: O(E(V + alpha(V))) — each edge triggers one root scan and DSU operations.
 * Space: O(V) — DSU arrays and vertex weights are stored.
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int *parent, *size;
long long *weight, *total;

int find(int u) {
    if (parent[u] != u) parent[u] = find(parent[u]);
    return parent[u];
}

void unite(int u, int v) {
    int a = find(u), b = find(v), t;
    if (a == b) return;
    if (size[a] < size[b]) { t = a; a = b; b = t; }
    parent[b] = a;
    size[a] += size[b];
    total[a] += total[b];
}

int main(void) {
    int V, E, K, i, j, u, v, root, found;
    long long best;

    if (scanf("%d %d %d", &V, &E, &K) != 3) return 0;
    if (V <= 0 || E < 0 || K < 1) return EXIT_FAILURE;
    parent = malloc((size_t)V * sizeof *parent);
    size = malloc((size_t)V * sizeof *size);
    weight = malloc((size_t)V * sizeof *weight);
    total = malloc((size_t)V * sizeof *total);
    if (!parent || !size || !weight || !total) {
        free(parent); free(size); free(weight); free(total);
        return EXIT_FAILURE;
    }
    for (i = 0; i < V; i++) {
        scanf("%lld", &weight[i]);
        parent[i] = i;
        size[i] = 1;
        total[i] = weight[i];
    }

    /* Merge every arriving edge; only components of at most K vertices qualify. */
    for (i = 0; i < E; i++) {
        scanf("%d %d", &u, &v);
        unite(u, v);
        best = LLONG_MIN;
        found = 0;
        for (j = 0; j < V; j++) {
            root = find(j);
            if (root == j && size[root] <= K) {
                found = 1;
                if (total[root] > best) best = total[root];
            }
        }
        if (!found) printf("NONE\n");
        else printf("%lld\n", best);
    }

    free(parent); free(size); free(weight); free(total);
    return 0;
}
