/*
 * Input: V, E, K, R, then K hubs, then E undirected edges.
 * Time: O(V + E) — standard multi-source BFS.
 * Space: O(V + E) — adjacency list, distance and owner arrays.
 */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int V, E, K, R;
    if (scanf("%d %d %d %d", &V, &E, &K, &R) != 4) return 1;

    int *head = malloc(V * sizeof(int));
    int *next = malloc(2 * E * sizeof(int));
    int *to = malloc(2 * E * sizeof(int));
    for (int i = 0; i < V; i++) head[i] = -1;

    int *hubs = malloc(K * sizeof(int));
    for (int i = 0; i < K; i++) scanf("%d", &hubs[i]);

    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        to[2 * i] = v; next[2 * i] = head[u]; head[u] = 2 * i;
        to[2 * i + 1] = u; next[2 * i + 1] = head[v]; head[v] = 2 * i + 1;
    }

    int *dist = malloc(V * sizeof(int));
    int *owner = malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) { dist[i] = -1; owner[i] = -1; }

    int *q = malloc((V + K) * sizeof(int));
    int front = 0, back = 0;

    // Initialize with all hubs
    for (int i = 0; i < K; i++) {
        int h = hubs[i];
        dist[h] = 0;
        owner[h] = i + 1;
        q[back++] = h;
    }

    while (front < back) {
        int u = q[front++];

        for (int e = head[u]; e != -1; e = next[e]) {
            int v = to[e];

            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                owner[v] = owner[u];
                q[back++] = v;
            } else if (dist[v] == dist[u] + 1) {
                if (owner[u] < owner[v]) {
                    owner[v] = owner[u];
                }
            }
        }
    }

    for (int i = 0; i < V; i++) {
        if (dist[i] == -1 || dist[i] > R) {
            printf("Vertex %d: owner -1, dist %d\n", i, dist[i]);
        } else {
            printf("Vertex %d: owner %d, dist %d\n", i, owner[i], dist[i]);
        }
    }

    free(head); free(next); free(to); free(hubs); free(dist); free(owner); free(q);
    return 0;
}