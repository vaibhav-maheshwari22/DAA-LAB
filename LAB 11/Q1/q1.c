/*
 * Input: V, E, S, C, then E directed edges (u, v, w).
 * Time: O(V + E) — 0-1 BFS on an expanded graph of 2V states.
 * Space: O(V + E) — adjacency list and distance array.
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int to, weight;
} Edge;

int main(void) {
    int V, E, S;
    long long C;
    if (scanf("%d %d %d %lld", &V, &E, &S, &C) != 4) return 1;

    // Expanded graph: state i (0 to V-1) = (vertex i, parity 0)
    // state i+V = (vertex i, parity 1)
    int V2 = 2 * V;
    int *head = malloc(V2 * sizeof(int));
    for (int i = 0; i < V2; i++) head[i] = -1;

    Edge *edges = malloc(2 * E * sizeof(Edge));
    int *next = malloc(2 * E * sizeof(int));
    int edge_cnt = 0;

    for (int i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        
        if (w == 0) {
            // (u, 0) -> (v, 0), cost 0
            edges[edge_cnt] = (Edge){v, 0}; next[edge_cnt] = head[u]; head[u] = edge_cnt++;
            // (u, 1) -> (v, 1), cost 0
            edges[edge_cnt] = (Edge){v + V, 0}; next[edge_cnt] = head[u + V]; head[u + V] = edge_cnt++;
        } else {
            // w == 1: (u, 0) -> (v, 1), cost 1
            edges[edge_cnt] = (Edge){v + V, 1}; next[edge_cnt] = head[u]; head[u] = edge_cnt++;
            // (u, 1) -> (v, 0), cost 1
            edges[edge_cnt] = (Edge){v, 1}; next[edge_cnt] = head[u + V]; head[u + V] = edge_cnt++;
        }
    }

    long long *dist = malloc(V2 * sizeof(long long));
    for (int i = 0; i < V2; i++) dist[i] = LLONG_MAX;
    
    // Deque using array (large enough for V2 states)
    int *dq = malloc((V2 + 2 * E + 10) * sizeof(int));
    int front = V2 + E + 5, back = V2 + E + 5; 
    
    dist[S] = 0; // start at S with parity 0
    dq[back++] = S;

    while (front < back) {
        int u = dq[front++];
        
        for (int e = head[u]; e != -1; e = next[e]) {
            int v = edges[e].to;
            int w = edges[e].weight;
            long long cost = w; // cost is just the edge weight (0 or 1)
            
            if (dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                if (cost == 0) {
                    dq[--front] = v; // Push to front for 0-cost
                } else {
                    dq[back++] = v;  // Push to back for 1-cost
                }
            }
        }
    }

    for (int i = 0; i < V; i++) {
        long long ans = LLONG_MAX;
        if (dist[i] != LLONG_MAX) ans = dist[i]; // even parity
        if (dist[i + V] != LLONG_MAX && dist[i + V] + C < ans) 
            ans = dist[i + V] + C; // odd parity + penalty

        if (ans == LLONG_MAX) printf("Vertex %d: Unreachable\n", i);
        else printf("Vertex %d: %lld\n", i, ans);
    }

    free(head); free(edges); free(next); free(dist); free(dq);
    return 0;
}