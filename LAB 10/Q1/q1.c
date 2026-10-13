/*
 * Input: V E, followed by E online edges u v with vertices numbered 0..V-1.
 * Time: O(E alpha(V)) — each edge performs a constant number of DSU operations.
 * Space: O(V) — parent, size, and parity arrays store the disjoint sets.
 */
#include <stdio.h>
#include <stdlib.h>

int *parent, *size, *parity;

int find(int u) {
    if (parent[u] != u) {
        int root = parent[u];
        parent[u] = find(root);
        parity[u] ^= parity[root];
    }
    return parent[u];
}

int main(void) {
    int V, E, i, u, v, r, c, k;

    if (scanf("%d %d", &V, &E) != 2) return 0;
    if (V <= 0 || E < 0) return EXIT_FAILURE;
    parent = malloc((size_t)V * sizeof *parent);
    size = malloc((size_t)V * sizeof *size);
    parity = calloc((size_t)V, sizeof *parity);
    if (!parent || !size || !parity) {
        free(parent);
        free(size);
        free(parity);
        return EXIT_FAILURE;
    }

    for (i = 0; i < V; i++) {
        parent[i] = i;
        size[i] = 1;
    }

    /* Add an edge only when it preserves opposite colors at its endpoints. */
    for (i = 0; i < E; i++) {
        scanf("%d %d", &u, &v);
        r = find(u);
        c = find(v);
        if (r == c) {
            if ((parity[u] ^ parity[v]) == 0)
                printf("Edge (%d, %d): violates bipartiteness; skipped\n", u, v);
            else
                printf("Edge (%d, %d): accepted\n", u, v);
        } else {
            if (size[r] < size[c]) { k = r; r = c; c = k; }
            parent[c] = r;
            parity[c] = parity[u] ^ parity[v] ^ 1;
            size[r] += size[c];
            printf("Edge (%d, %d): accepted\n", u, v);
        }
    }

    printf("Graph remains bipartite.\n");
    free(parent);
    free(size);
    free(parity);
    return 0;
}
