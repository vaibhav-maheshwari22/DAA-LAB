
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long start, end;
    int id;
} Meeting;

typedef struct {
    long long end;
    int room;
} Active;

static int compareMeeting(const void *a, const void *b) {
    const Meeting *x = a, *y = b;
    if (x->start < y->start) return -1;
    if (x->start > y->start) return 1;
    if (x->end < y->end) return -1;
    if (x->end > y->end) return 1;
    return x->id - y->id;
}

// Min-heap keyed by meeting end time
static void push(Active *heap, int *size, Active value) {
    int i = (*size)++;
    while (i > 0 && heap[(i - 1) / 2].end > value.end) {
        heap[i] = heap[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap[i] = value;
}

static Active pop(Active *heap, int *size) {
    int i = 0, end = --(*size);
    Active result = heap[0], value;
    if (end == 0)
        return result;
    value = heap[end];
    while (2 * i + 1 < end) {
        int child = 2 * i + 1;
        if (child + 1 < end && heap[child + 1].end < heap[child].end)
            child++;
        if (heap[child].end >= value.end)
            break;
        heap[i] = heap[child];
        i = child;
    }
    heap[i] = value;
    return result;
}

int main(void) {
    int n, i;
    int activeCount = 0, freeCount = 0, rooms = 0;
    Meeting *meetings;
    Active *active;
    int *assigned, *freeRooms;

    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid meeting count.\n");
        return 1;
    }

    meetings  = malloc((size_t)(n == 0 ? 1 : n) * sizeof(*meetings));
    active    = malloc((size_t)(n == 0 ? 1 : n) * sizeof(*active));
    assigned  = malloc((size_t)(n == 0 ? 1 : n) * sizeof(*assigned));
    freeRooms = malloc((size_t)(n == 0 ? 1 : n) * sizeof(*freeRooms));

    if (!meetings || !active || !assigned || !freeRooms) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(meetings); free(active); free(assigned); free(freeRooms);
        return 1;
    }

    for (i = 0; i < n; i++) {
        if (scanf("%lld%lld", &meetings[i].start, &meetings[i].end) != 2 ||
            meetings[i].start > meetings[i].end) {
            fprintf(stderr, "Invalid meeting interval.\n");
            free(meetings); free(active); free(assigned); free(freeRooms);
            return 1;
        }
        meetings[i].id = i;
    }

    // Sort by start time so we process meetings in chronological order
    qsort(meetings, (size_t)n, sizeof(*meetings), compareMeeting);

    for (i = 0; i < n; i++) {
        // Free rooms whose meetings already ended by this start time
        while (activeCount > 0 && active[0].end <= meetings[i].start) {
            Active ended = pop(active, &activeCount);
            freeRooms[freeCount++] = ended.room;
        }

        // Reuse a freed room if possible, else open a new one
        if (freeCount > 0) {
            assigned[meetings[i].id] = freeRooms[--freeCount];
        } else {
            assigned[meetings[i].id] = ++rooms;
        }

        // Register this meeting as active
        Active now;
        now.end = meetings[i].end;
        now.room = assigned[meetings[i].id];
        push(active, &activeCount, now);
    }

    printf("Minimum rooms: %d\n", rooms);
    printf("Meeting room assignments:\n");
    for (i = 0; i < n; i++)
        printf("%d %d\n", i + 1, assigned[i]);

    free(meetings); free(active); free(assigned); free(freeRooms);
    return 0;
}