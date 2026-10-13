/*
 * Input: V E, V vertex weights, E undirected edges, then V deleted vertices.
 * Time: O(V^2 + E alpha(V)) — each reverse insertion scans DSU roots.
 * Space: O(V + E) — adjacency lists, DSU state, and saved answers are stored.
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Edge {
    int to, next;
} Edge;

int *head, *parent, *size, *active, *order;
long long *weight, *total, *answer;
Edge *edges;

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
    int V, E, i, u, v, e, root, any;
    long long best;

    if (scanf("%d %d", &V, &E) != 2) return 0;
    if (V <= 0 || E < 0) return EXIT_FAILURE;
    head = malloc((size_t)V * sizeof *head);
    parent = malloc((size_t)V * sizeof *parent);
    size = malloc((size_t)V * sizeof *size);
    active = calloc((size_t)V, sizeof *active);
    order = malloc((size_t)V * sizeof *order);
    weight = malloc((size_t)V * sizeof *weight);
    total = malloc((size_t)V * sizeof *total);
    answer = malloc((size_t)V * sizeof *answer);
    edges = malloc((size_t)2 * (size_t)E * sizeof *edges);
    if (!head || !parent || !size || !active || !order || !weight ||
        !total || !answer || !edges) {
        free(head); free(parent); free(size); free(active); free(order);
        free(weight); free(total); free(answer); free(edges);
        return EXIT_FAILURE;
    }
    for (i = 0; i < V; i++) { head[i] = -1; parent[i] = -1; }
    for (i = 0; i < V; i++) scanf("%lld", &weight[i]);
    for (i = 0; i < E; i++) {
        scanf("%d %d", &u, &v);
        edges[2 * i] = (Edge){v, head[u]};
        head[u] = 2 * i;
        edges[2 * i + 1] = (Edge){u, head[v]};
        head[v] = 2 * i + 1;
    }
    for (i = 0; i < V; i++) scanf("%d", &order[i]);

    /* Reverse deletions: the answer before restoring a vertex is its forward state. */
    best = 0;
    for (i = V - 1; i >= 0; i--) {
        answer[i] = best;
        u = order[i];
        parent[u] = u;
        size[u] = 1;
        total[u] = weight[u];
        active[u] = 1;
        for (e = head[u]; e != -1; e = edges[e].next)
            if (active[edges[e].to]) unite(u, edges[e].to);

        best = LLONG_MIN;
        any = 0;
        for (v = 0; v < V; v++) {
            root = active[v] ? find(v) : -1;
            if (active[v] && root == v) {
                any = 1;
                if (total[root] > best) best = total[root];
            }
        }
        if (!any) best = 0;
    }
    for (i = 0; i < V; i++) printf("%lld\n", answer[i]);

    free(head); free(parent); free(size); free(active);
    free(order); free(weight); free(total); free(answer); free(edges);
    return 0;
}
