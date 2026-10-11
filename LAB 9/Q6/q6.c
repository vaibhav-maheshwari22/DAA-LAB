
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define ALPHABET 256

// Read a whitespace-delimited word of arbitrary length
static char *readWord(void) {
    size_t cap = 32, len = 0;
    char *buf = malloc(cap);
    int c;
    if (!buf) return NULL;

    // Skip leading whitespace
    do { c = getchar(); } while (c != EOF && (c == ' ' || c == '\n' || c == '\t' || c == '\r'));
    if (c == EOF) { free(buf); return NULL; }

    // Read until next whitespace
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

int main(void) {
    int K, i, j, best;
    int count[ALPHABET] = {0};
    int last[ALPHABET];
    int impossible = 0;

    if (scanf("%d", &K) != 1 || K < 0) {
        fprintf(stderr, "Invalid K.\n");
        return 1;
    }

    char *s = readWord();
    if (!s) {
        fprintf(stderr, "Missing input string.\n");
        return 1;
    }

    size_t n = strlen(s);
    char *result = malloc(n + 1);
    if (!result) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(s);
        return 1;
    }

    // Track last used position of each character (init to very negative)
    for (i = 0; i < ALPHABET; i++)
        last[i] = INT_MIN / 2;

    // Frequency of each character
    for (i = 0; i < (int)n; i++)
        count[(unsigned char)s[i]]++;

    // Greedy placement
    for (i = 0; i < (int)n; i++) {
        best = -1;
        for (j = 0; j < ALPHABET; j++) {
            if (count[j] > 0 && i - last[j] >= K &&
                (best == -1 || count[j] > count[best]))
                best = j;
        }
        if (best == -1) { impossible = 1; break; }
        result[i] = (char)best;
        count[best]--;
        last[best] = i;
    }

    if (impossible) {
        printf("Rearranged string: \n");
    } else {
        result[n] = '\0';
        printf("Rearranged string: %s\n", result);
        printf("Position trace:\n");
        for (i = 0; i < (int)n; i++)
            printf("  pos %2d : %c\n", i, result[i]);
    }

    free(s);
    free(result);
    return 0;
}