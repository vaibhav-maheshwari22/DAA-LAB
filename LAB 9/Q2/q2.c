#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned long long freq;
    int left, right;
    char symbol;
} Node;

typedef struct {
    int *a;
    int size;
    Node *nodes;
} Heap;

// Min-heap compare: smaller frequency first; tie broken by smaller index
static int lessNode(Heap *h, int a, int b) {
    if (h->nodes[a].freq != h->nodes[b].freq)
        return h->nodes[a].freq < h->nodes[b].freq;
    return a < b;
}

static void push(Heap *h, int value) {
    int i = h->size++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (!lessNode(h, value, h->a[p])) break;
        h->a[i] = h->a[p];
        i = p;
    }
    h->a[i] = value;
}

static int pop(Heap *h) {
    int result = h->a[0];
    int value = h->a[--h->size];
    int i = 0;
    while (2 * i + 1 < h->size) {
        int child = 2 * i + 1;
        if (child + 1 < h->size && lessNode(h, h->a[child + 1], h->a[child]))
            child++;
        if (!lessNode(h, h->a[child], value)) break;
        h->a[i] = h->a[child];
        i = child;
    }
    if (h->size > 0) h->a[i] = value;
    return result;
}

// Walk tree; record leaf depth into lengths[] by character index
static void getLengths(Node *nodes, int id, int depth, int *lengths) {
    if (nodes[id].left == -1) {
        lengths[(unsigned char)nodes[id].symbol] = depth == 0 ? 1 : depth;
        return;
    }
    getLengths(nodes, nodes[id].left, depth + 1, lengths);
    getLengths(nodes, nodes[id].right, depth + 1, lengths);
}

typedef struct {
    char symbol;
    int length;
} Code;

static int compareCode(const void *a, const void *b) {
    const Code *x = a, *y = b;
    if (x->length != y->length) return x->length - y->length;
    return (unsigned char)x->symbol - (unsigned char)y->symbol;
}

int main(void) {
    int n, i, count = 0, *lengths;
    Node *nodes;
    Heap heap;
    Code *codes;
    char **bits;

    if (scanf("%d", &n) != 1 || n < 1 || n > 1000) {
        fprintf(stderr, "Invalid symbol count.\n");
        return 1;
    }

    nodes = calloc((size_t)(2 * n - 1), sizeof(*nodes));
    heap.a = malloc((size_t)n * sizeof(*heap.a));
    lengths = calloc(256, sizeof(*lengths));
    codes = malloc((size_t)n * sizeof(*codes));
    bits = calloc((size_t)n, sizeof(*bits));

    if (!nodes || !heap.a || !lengths || !codes || !bits) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    heap.nodes = nodes;
    heap.size = 0;

    // Read symbols and build initial heap
    for (i = 0; i < n; i++) {
        char symbol;
        unsigned long long freq;
        if (scanf(" %c%llu", &symbol, &freq) != 2 || freq == 0 ||
            lengths[(unsigned char)symbol] != 0) {
            fprintf(stderr, "Invalid or duplicate symbol data.\n");
            return 1;
        }
        nodes[i].symbol = symbol;
        nodes[i].freq = freq;
        nodes[i].left = nodes[i].right = -1;
        lengths[(unsigned char)symbol] = -1;   // mark as used
        push(&heap, i);
    }
    memset(lengths, 0, 256 * sizeof(*lengths));

    // Build Huffman tree: merge two least-frequent nodes each step
    while (heap.size > 1) {
        int a = pop(&heap), b = pop(&heap), id = n + count++;
        nodes[id].left = a;
        nodes[id].right = b;
        nodes[id].freq = nodes[a].freq + nodes[b].freq;
        push(&heap, id);
    }
    getLengths(nodes, pop(&heap), 0, lengths);

    // Collect leaves with their code lengths
    count = 0;
    for (i = 0; i < 256; i++) {
        if (lengths[i] > 0) {
            codes[count].symbol = (char)i;
            codes[count].length = lengths[i];
            count++;
        }
    }
    qsort(codes, (size_t)n, sizeof(*codes), compareCode);

    // Generate canonical codes
    for (i = 0; i < n; i++) {
        bits[i] = malloc((size_t)codes[i].length + 1);
        if (!bits[i]) {
            fprintf(stderr, "Memory allocation failed.\n");
            return 1;
        }

        if (i == 0) {
            // First code: all zeros
            memset(bits[i], '0', (size_t)codes[i].length);
        } else {
            // Copy previous, then add 1 in binary
            strcpy(bits[i], bits[i - 1]);
            int k = codes[i - 1].length - 1;
            while (k >= 0 && bits[i][k] == '1') bits[i][k--] = '0';
            if (k >= 0) bits[i][k] = '1';
            else        bits[i][0] = '1';

            // If length increased, right-pad with zeros
            if (codes[i].length > codes[i - 1].length) {
                int oldLen = codes[i - 1].length;
                memset(bits[i] + oldLen, '0',
                       (size_t)(codes[i].length - oldLen));
            }
        }
        bits[i][codes[i].length] = '\0';
    }

    printf("Symbol Length CanonicalCode\n");
    for (i = 0; i < n; i++)
        printf("%c %d %s\n", codes[i].symbol, codes[i].length, bits[i]);

    for (i = 0; i < n; i++) free(bits[i]);
    free(nodes); free(heap.a); free(lengths); free(codes); free(bits);
    return 0;
}