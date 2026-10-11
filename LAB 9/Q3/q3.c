
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long d, f;
    int id;
} Station;

static int compareStation(const void *a, const void *b) {
    const Station *x = a, *y = b;
    if (x->d < y->d) return -1;
    if (x->d > y->d) return 1;
    return x->id - y->id;
}

// Max-heap keyed by fuel amount
static void push(Station *heap, int *size, Station value) {
    int i = (*size)++;
    while (i > 0 && heap[(i - 1) / 2].f < value.f) {
        heap[i] = heap[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap[i] = value;
}

static Station pop(Station *heap, int *size) {
    int i = 0, end = --(*size);
    Station result = heap[0], value;
    if (end == 0)
        return result;
    value = heap[end];
    while (2 * i + 1 < end) {
        int child = 2 * i + 1;
        if (child + 1 < end && heap[child + 1].f > heap[child].f)
            child++;
        if (heap[child].f <= value.f)
            break;
        heap[i] = heap[child];
        i = child;
    }
    heap[i] = value;
    return result;
}

int main(void) {
    long long D, fuel, previous = 0;
    int n, i, size = 0, stops = 0, possible = 1;
    Station *s, *heap, *chosen;

    if (scanf("%lld%lld%d", &D, &fuel, &n) != 3 ||
        D < 0 || fuel < 0 || n < 0) {
        fprintf(stderr, "Invalid trip data.\n");
        return 1;
    }

    s      = malloc((size_t)(n == 0 ? 1 : n) * sizeof(*s));
    heap   = malloc((size_t)(n == 0 ? 1 : n) * sizeof(*heap));
    chosen = malloc((size_t)(n == 0 ? 1 : n) * sizeof(*chosen));

    if (!s || !heap || !chosen) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(s); free(heap); free(chosen);
        return 1;
    }

    for (i = 0; i < n; i++) {
        if (scanf("%lld%lld", &s[i].d, &s[i].f) != 2 ||
            s[i].d < 0 || s[i].d > D || s[i].f < 0) {
            fprintf(stderr, "Invalid station data.\n");
            free(s); free(heap); free(chosen);
            return 1;
        }
        s[i].id = i + 1;
    }

    // Sort stations by distance; ties broken by original id
    qsort(s, (size_t)n, sizeof(*s), compareStation);

    for (i = 0; i <= n; i++) {
        long long destination = (i == n) ? D : s[i].d;

        // If fuel is not enough to reach the next point, refuel from the
        // best station we already passed (max-heap)
        while (fuel < destination - previous) {
            if (size == 0) {
                possible = 0;
                break;
            }
            chosen[stops++] = pop(heap, &size);
            fuel += chosen[stops - 1].f;
        }
        if (!possible) break;

        fuel -= destination - previous;
        previous = destination;

        // Add the current station to the available pool
        if (i < n)
            push(heap, &size, s[i]);
    }

    if (!possible) {
        printf("Impossible\n");
    } else {
        // Present chosen stops in station-id order for readability
        qsort(chosen, (size_t)stops, sizeof(*chosen), compareStation);
        printf("Minimum stops: %d\n", stops);
        printf("Stops (station IDs):");
        for (i = 0; i < stops; i++)
            printf(" %d", chosen[i].id);
        printf("\n");
    }

    free(s); free(heap); free(chosen);
    return 0;
}