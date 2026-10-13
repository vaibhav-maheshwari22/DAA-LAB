/*
 * Input: n m, a permutation of 1..n, then m swappable pairs u v (vertices 0..n-1).
 * Time: O((n + m) alpha(n) + n log n) — DSU groups and sorted component values.
 * Space: O(n) — DSU arrays and two arrays of sortable component entries.
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct Item {
    int root, value, index;
} Item;

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

int by_position(const void *x, const void *y) {
    const Item *a = x, *b = y;
    if (a->root != b->root) return (a->root > b->root) - (a->root < b->root);
    return (a->index > b->index) - (a->index < b->index);
}

int by_value(const void *x, const void *y) {
    const Item *a = x, *b = y;
    if (a->root != b->root) return (a->root > b->root) - (a->root < b->root);
    return (a->value > b->value) - (a->value < b->value);
}

int main(void) {
    int n, m, i, u, v, *answer;
    Item *positions, *values;

    if (scanf("%d %d", &n, &m) != 2) return 0;
    if (n <= 0 || m < 0) return EXIT_FAILURE;
    parent = malloc((size_t)n * sizeof *parent);
    size = malloc((size_t)n * sizeof *size);
    answer = malloc((size_t)n * sizeof *answer);
    positions = malloc((size_t)n * sizeof *positions);
    values = malloc((size_t)n * sizeof *values);
    if (!parent || !size || !answer || !positions || !values) {
        free(parent); free(size); free(answer); free(positions); free(values);
        return EXIT_FAILURE;
    }
    for (i = 0; i < n; i++) {
        scanf("%d", &v);
        parent[i] = i;
        size[i] = 1;
        positions[i] = (Item){i, 0, i};
        values[i] = (Item){i, v, i};
    }
    for (i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        unite(u, v);
    }
    for (i = 0; i < n; i++) {
        positions[i].root = find(i);
        values[i].root = positions[i].root;
    }
    qsort(positions, (size_t)n, sizeof *positions, by_position);
    qsort(values, (size_t)n, sizeof *values, by_value);
    for (i = 0; i < n; i++) answer[positions[i].index] = values[i].value;
    for (i = 0; i < n; i++) printf("%d%c", answer[i], i + 1 == n ? '\n' : ' ');

    free(parent); free(size); free(answer); free(positions); free(values);
    return 0;
}
