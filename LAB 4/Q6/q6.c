/*
 * Description: sweep-line algorithm to identify a 
 * point on the line that is in the largest number of intervals.
 */

#include <stdio.h>
#include <stdlib.h>

// Struct to represent an endpoint event
typedef struct {
    int coord;
    int type; // 1 for start (left), -1 for end (right)
} Event;

void get_data(Event *arr, int n);
int compare_events(const void *a, const void *b);
void find_max_point(Event *arr, int total_events);

int main() {
    int n;

    printf("Point in Maximum Intervals\n");
    printf("--------------------------\n");
    printf("Enter the number of intervals (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size!\n");
        return 1;
    }

    // Dynamically allocate memory for 2*n events (left and right endpoints)
    Event *events = (Event *)malloc(2 * n * sizeof(Event));

    if (events == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Take input from the user
    get_data(events, n);

    // Sort the events based on coordinates
    qsort(events, 2 * n, sizeof(Event), compare_events);

    // Find the point with maximum overlaps
    find_max_point(events, 2 * n);

    // Free the allocated memory
    free(events);
    return 0;
}

// User input function
void get_data(Event *arr, int n) {
    printf("\nEnter %d intervals (left and right endpoints):\n", n);
    for (int i = 0; i < n; i++) {
        int left, right;
        printf("Interval %d: ", i + 1);
        scanf("%d %d", &left, &right);
        
        // Store left endpoint (start of interval)
        arr[2 * i].coord = left;
        arr[2 * i].type = 1;
        
        // Store right endpoint (end of interval)
        arr[2 * i + 1].coord = right;
        arr[2 * i + 1].type = -1;
    }
}

// Comparator function for qsort
int compare_events(const void *a, const void *b) {
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;
    
    if (e1->coord == e2->coord) {
        /*
        *If coordinates are same, process start (+1) before end (-1)
        *because endpoints count as being in the interval.
        */
        return e2->type - e1->type; 
    }
    return e1->coord - e2->coord;
}

// to find the point in the largest number of intervals
void find_max_point(Event *arr, int total_events) {
    int current_overlap = 0;
    int max_overlap = 0;
    int best_point = -1;

    for (int i = 0; i < total_events; i++) {
        current_overlap += arr[i].type;

        if (current_overlap > max_overlap) {
            max_overlap = current_overlap;
            best_point = arr[i].coord;
        }
    }

    printf("\nResult: Point %d is in the largest number of intervals (%d intervals).\n", best_point, max_overlap);
}