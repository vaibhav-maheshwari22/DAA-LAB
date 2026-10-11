
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    long long value;
    int id;
} Item;

// Max-heap keyed by value
static void push(Item *heap, int *size, Item value) {
    int i = (*size)++;
    while (i > 0 && heap[(i - 1) / 2].value < value.value) {
        heap[i] = heap[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap[i] = value;
}

static Item pop(Item *heap, int *size) {
    int i = 0, end = --(*size);
    Item result = heap[0], value;
    if (end == 0)
        return result;
    value = heap[end];
    while (2 * i + 1 < end) {
        int child = 2 * i + 1;
        if (child + 1 < end && heap[child + 1].value > heap[child].value)
            child++;
        if (heap[child].value <= value.value)
            break;
        heap[i] = heap[child];
        i = child;
    }
    heap[i] = value;
    return result;
}

int main(void) {
    int n, i, size = 0, step = 0;
    long long minimum = LLONG_MAX;
    long long best = LLONG_MAX;
    long long *value;
    Item *heap;

    if (scanf("%d", &n) != 1 || n < 1) {
        fprintf(stderr, "Invalid array size.\n");
        return 1;
    }

    value = malloc((size_t)n * sizeof(*value));
    heap  = malloc((size_t)n * sizeof(*heap));

    if (!value || !heap) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(value); free(heap);
        return 1;
    }

    // Bring every odd value to its even baseline by doubling once.
    // Track the minimum, and push each value into the max-heap.
    for (i = 0; i < n; i++) {
        long long x;
        if (scanf("%lld", &x) != 1 || x <= 0 || x > INT_MAX) {
            fprintf(stderr, "Values must be positive integers.\n");
            free(value); free(heap);
            return 1;
        }
        value[i] = (x & 1) ? x * 2 : x;
        if (value[i] < minimum) minimum = value[i];

        Item it = { value[i], i };
        push(heap, &size, it);
    }

    printf("Trace (step, maximum, minimum, deviation):\n");

    // Repeatedly halve the current maximum while it is even.
    while (size > 0) {
        Item top = pop(heap, &size);
        long long deviation = top.value - minimum;

        printf("%d %lld %lld %lld\n", step++, top.value, minimum, deviation);
        if (deviation < best) best = deviation;

        // If the max is odd, we cannot halve it any further — stop.
        if (top.value & 1) break;

        top.value /= 2;
        value[top.id] = top.value;
        if (top.value < minimum) minimum = top.value;
        push(heap, &size, top);
    }

    printf("Minimum deviation: %lld\n", best);
    printf("Final array:");
    for (i = 0; i < n; i++) printf(" %lld", value[i]);
    printf("\n");

    free(value); free(heap);
    return 0;
}