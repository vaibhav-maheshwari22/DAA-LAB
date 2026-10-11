
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Read one whitespace-delimited word of arbitrary length
static char *readWord(void) {
    size_t cap = 32, len = 0;
    char *buf = malloc(cap);
    int c;
    if (!buf) return NULL;

    do { c = getchar(); }
    while (c != EOF && (c == ' ' || c == '\n' || c == '\t' || c == '\r'));

    if (c == EOF) { free(buf); return NULL; }

    while (c != EOF && c != ' ' && c != '\n' && c != '\t' && c != '\r') {
        if (len + 1 >= cap) {
            cap *= 2;
            char *tmp = realloc(buf, cap);
            if (!tmp) { free(buf); return NULL; }
            buf = tmp;
        }
        buf[len++] = (char)c;
        c = getchar();
    }
    buf[len] = '\0';
    return buf;
}

// Largest k such that suffix of `a` of length k equals prefix of `b` of length k
static size_t overlap(const char *a, const char *b) {
    size_t la = strlen(a), lb = strlen(b);
    size_t limit = la < lb ? la : lb;
    for (size_t k = limit; k > 0; k--) {
        if (memcmp(a + la - k, b, k) == 0)
            return k;
    }
    return 0;
}

// Merge a and b with the given overlap: a + b[shared..]
static char *mergeStrings(const char *a, const char *b, size_t shared) {
    size_t la = strlen(a), lb = strlen(b);
    size_t len = la + lb - shared;
    char *m = malloc(len + 1);
    if (!m) return NULL;
    memcpy(m, a, la);
    memcpy(m + la, b + shared, lb - shared);
    m[len] = '\0';
    return m;
}

int main(void) {
    int n, count, i;

    if (scanf("%d", &n) != 1 || n < 1) {
        fprintf(stderr, "Invalid string count.\n");
        return 1;
    }

    char **strings = malloc((size_t)n * sizeof(*strings));
    if (!strings) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    count = n;
    for (i = 0; i < n; i++) {
        strings[i] = readWord();
        if (!strings[i]) {
            fprintf(stderr, "Missing string or allocation failed.\n");
            while (i > 0) free(strings[--i]);
            free(strings);
            return 1;
        }
    }

    // Greedily merge the pair with the maximum overlap until one remains
    for (i = 1; count > 1; i++) {
        int aIndex = -1, bIndex = -1, reverse = 0;
        size_t bestOverlap = 0;

        // Try every ordered pair; keep the best overlap (either direction)
        for (int a = 0; a < count; a++) {
            for (int b = a + 1; b < count; b++) {
                size_t fwd = overlap(strings[a], strings[b]);
                size_t bwd = overlap(strings[b], strings[a]);
                if (aIndex == -1 || fwd > bestOverlap) {
                    bestOverlap = fwd;
                    aIndex = a; bIndex = b; reverse = 0;
                }
                if (bwd > bestOverlap) {
                    bestOverlap = bwd;
                    aIndex = a; bIndex = b; reverse = 1;
                }
            }
        }

        // Merge the winning pair
        const char *first  = reverse ? strings[bIndex] : strings[aIndex];
        const char *second = reverse ? strings[aIndex] : strings[bIndex];
        char *merged = mergeStrings(first, second, bestOverlap);
        if (!merged) {
            fprintf(stderr, "Memory allocation failed.\n");
            for (int a = 0; a < count; a++) free(strings[a]);
            free(strings);
            return 1;
        }

        printf("Merge %d (overlap %zu): %s\n", i, bestOverlap, merged);

        // Replace the pair with the merged string; compact the array
        free(strings[aIndex]);
        free(strings[bIndex]);
        strings[aIndex] = merged;
        for (int a = bIndex; a < count - 1; a++)
            strings[a] = strings[a + 1];
        count--;
    }

    printf("Greedy superstring: %s\n", strings[0]);

    for (i = 0; i < count; i++) free(strings[i]);
    free(strings);
    return 0;
}