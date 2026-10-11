#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long a, b, sum;
} Merge;

// Min-heap of long long
static void push(long long *heap, int *size, long long value) {
    int i = (*size)++;
    while (i > 0 && heap[(i - 1) / 2] > value) {
        heap[i] = heap[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap[i] = value;
}

static long long pop(long long *heap, int *size) {
    long long result = heap[0];
    long long value = heap[--(*size)];
    int i = 0;
    while (2 * i + 1 < *size) {
        int child = 2 * i + 1;
        if (child + 1 < *size && heap[child + 1] < heap[child])
            child++;
        if (heap[child] >= value) break;
        heap[i] = heap[child];
        i = child;
    }
    if (*size > 0) heap[i] = value;
    return result;
}

int main(void) {
    int n, i, size;
    long long total = 0;
    long long *heap;
    Merge *trace;

    if (scanf("%d", &n) != 1 || n < 1) {
        fprintf(stderr, "Invalid stick count.\n");
        return 1;
    }

    heap  = malloc((size_t)n * sizeof(*heap));
    trace = malloc((size_t)(n - 1) * sizeof(*trace));

    if (heap == NULL || (n > 1 && trace == NULL)) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(heap); free(trace);
        return 1;
    }

    size = 0;
    for (i = 0; i < n; i++) {
        long long length;
        if (scanf("%lld", &length) != 1 || length < 0) {
            fprintf(stderr, "Invalid stick length.\n");
            free(heap); free(trace);
            return 1;
        }
        push(heap, &size, length);
    }

    // Merge the two smallest each step; record each merge for output
    for (i = 0; i < n - 1; i++) {
        long long a = pop(heap, &size);
        long long b = pop(heap, &size);
        long long sum = a + b;
        trace[i].a = a;
        trace[i].b = b;
        trace[i].sum = sum;
        total += sum;
        push(heap, &size, sum);
    }

    printf("Minimum cost: %lld\n", total);
    printf("Merges (first, second, result):\n");
    for (i = 0; i < n - 1; i++)
        printf("%lld %lld %lld\n", trace[i].a, trace[i].b, trace[i].sum);

    free(heap);
    free(trace);
    return 0;
}