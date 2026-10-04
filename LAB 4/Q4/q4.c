/*
 * Description: Algorithm to determine the time when the 
 * most people were simultaneously present at the party.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int time;
    int type; // 1 for entry, -1 for exit
} Event;

void get_data(Event *arr, int n);
int compare_events(const void *a, const void *b);
void find_peak_time(Event *arr, int total_events);

int main() {
    int n;

    printf("Party Peak Attendance Search\n");
    printf("----------------------------\n");
    printf("Enter the number of persons (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size!\n");
        return 1;
    }

    // Dynamically allocate memory for 2*n events (entry and exit)
    Event *events = (Event *)malloc(2 * n * sizeof(Event));

    if (events == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Take input from the user
    get_data(events, n);

    // Sort the events based on time
    qsort(events, 2 * n, sizeof(Event), compare_events);

    // Find the time with maximum people
    find_peak_time(events, 2 * n);

    // Free the allocated memory
    free(events);
    return 0;
}

// User input function
void get_data(Event *arr, int n) {
    printf("\nEnter entry and exit times for %d persons:\n", n);
    for (int i = 0; i < n; i++) {
        int entry, exit_time;
        printf("Person %d (Entry Exit): ", i + 1);
        scanf("%d %d", &entry, &exit_time);
        
        // Store entry event
        arr[2 * i].time = entry;
        arr[2 * i].type = 1;
        
        // Store exit event
        arr[2 * i + 1].time = exit_time;
        arr[2 * i + 1].type = -1;
    }
}

// Comparator function for qsort
int compare_events(const void *a, const void *b) {
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;
    
    if (e1->time == e2->time) {
        // If times are same, process exits before entries
        return e1->type - e2->type; 
    }
    return e1->time - e2->time;
}

// to find max overlapping intervals
void find_peak_time(Event *arr, int total_events) {
    int current_count = 0;
    int max_count = 0;
    int peak_time = -1;

    for (int i = 0; i < total_events; i++) {
        current_count += arr[i].type;

        if (current_count > max_count) {
            max_count = current_count;
            peak_time = arr[i].time;
        }
    }

    printf("\nResult: Maximum people present were %d at time %d.\n", max_count, peak_time);
}