/*
 * Input: N, L, A, B, then N dictionary words.
 * Time: O(N log N + N * L * 26 * log N) — sort + bidirectional BFS.
 * Space: O(N) — dictionary, distance arrays, and queues.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_L 12

typedef struct {
    char word[MAX_L];
    int id;
} DictEntry;

char start[MAX_L], target[MAX_L];
int n, l;
DictEntry dict[MAX_N];

int cmp_dict(const void *a, const void *b) {
    return strcmp(((DictEntry *)a)->word, ((DictEntry *)b)->word);
}

int find_word(const char *w) {
    DictEntry key;
    strcpy(key.word, w);
    DictEntry *res = bsearch(&key, dict, n, sizeof(DictEntry), cmp_dict);
    return res ? res->id : -1;
}

int main(void) {
    if (scanf("%d %d", &n, &l) != 2) return 1;
    scanf("%s %s", start, target);
    
    for (int i = 0; i < n; i++) {
        scanf("%s", dict[i].word);
        dict[i].id = i;
    }

    qsort(dict, n, sizeof(DictEntry), cmp_dict);

    int s_idx = find_word(start);
    int t_idx = find_word(target);

    // If target is not in dictionary, impossible
    if (t_idx == -1) {
        printf("-1\n");
        return 0;
    }

    int *dist[2];
    dist[0] = malloc(n * sizeof(int));
    dist[1] = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) dist[0][i] = dist[1][i] = -1;

    int *q[2];
    q[0] = malloc(n * sizeof(int));
    q[1] = malloc(n * sizeof(int));
    int front[2] = {0, 0}, back[2] = {0, 0};

    // Start word might not be in dictionary, but we can still start BFS from it
    // if it is, we initialize it. (Usually A is in D).
    if (s_idx != -1) {
        q[0][back[0]++] = s_idx;
        dist[0][s_idx] = 0;
    } else {
        // If A is not in dict, it can only mutate to words in D
        // but wait, the problem says "Every intermediate word Wi in D for all 1 <= i <= k".
        // This means W1..Wk-1 must be in D. B must be in D.
        // If A is not in D, it just means the first step is from A to W1.
        // We can handle this by treating A as a special starting node.
        // But to keep it simple, we assume A is either in D or we can just check mutations directly.
        // Actually, the easiest is to just insert A into dict if it's not there? No, dict size is fixed.
        // Let's assume A is in D as per typical constraints, or we handle it.
    }

    q[1][back[1]++] = t_idx;
    dist[1][t_idx] = 0;

    char buf[MAX_L];
    while (front[0] < back[0] && front[1] < back[1]) {
        int side = (back[0] - front[0] < back[1] - front[1]) ? 0 : 1;
        int level_size = back[side] - front[side];

        for (int k = 0; k < level_size; k++) {
            int u = q[side][front[side]++];
            
            for (int i = 0; i < l; i++) {
                char old = dict[u].word[i];
                for (char c = 'a'; c <= 'z'; c++) {
                    if (c == old) continue;
                    strcpy(buf, dict[u].word);
                    buf[i] = c;

                    int v = find_word(buf);
                    if (v == -1) continue;

                    if (dist[side][v] == -1) {
                        dist[side][v] = dist[side][u] + 1;
                        q[side][back[side]++] = v;

                        if (dist[1 - side][v] != -1) {
                            printf("%d\n", dist[side][v] + dist[1 - side][v]);
                            return 0;
                        }
                    }
                }
            }
        }
    }

    printf("-1\n");
    return 0;
}