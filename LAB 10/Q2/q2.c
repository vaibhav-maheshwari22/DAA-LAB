/*
 * Input: R C k, followed by k land-cell coordinates r c, numbered from zero.
 * Time: O(k alpha(RC)) — each insertion checks at most four neighboring cells.
 * Space: O(RC) — flattened cells store their DSU parent and component size.
 */
#include <stdio.h>
#include <stdlib.h>

int *parent, *size;

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
}

int main(void) {
    int R, C, k, cells, i, r, c, nr, nc, id, neighbor, islands;
    int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};

    if (scanf("%d %d %d", &R, &C, &k) != 3) return 0;
    if (R <= 0 || C <= 0 || k < 0 || R > 2147483647 / C)
        return EXIT_FAILURE;
    cells = R * C;
    parent = malloc((size_t)cells * sizeof *parent);
    size = malloc((size_t)cells * sizeof *size);
    if (!parent || !size) {
        free(parent);
        free(size);
        return EXIT_FAILURE;
    }
    for (i = 0; i < cells; i++) parent[i] = -1;
    islands = 0;

    /* Activate each cell once, then merge it with its existing land neighbors. */
    for (i = 0; i < k; i++) {
        scanf("%d %d", &r, &c);
        id = r * C + c;
        if (parent[id] == -1) {
            parent[id] = id;
            size[id] = 1;
            islands++;
            for (int j = 0; j < 4; j++) {
                nr = r + dr[j];
                nc = c + dc[j];
                if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                neighbor = nr * C + nc;
                if (parent[neighbor] != -1 && find(id) != find(neighbor)) {
                    unite(id, neighbor);
                    islands--;
                }
            }
        }
        printf("%d%c", islands, i + 1 == k ? '\n' : ' ');
    }

    free(parent);
    free(size);
    return 0;
}
