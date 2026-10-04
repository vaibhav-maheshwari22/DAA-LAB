#include <stdio.h>
#include <stdlib.h>

// Structure representing an event along the timeline
typedef struct {
    int year;
    int type; // -1 for death, +1 for birth
} Event;


int compare_events(const void *a, const void *b);
void get_data(Event **events, int *n);
void find_best_year(Event *events, int n, int *best_year, int *max_alive);
void display_results(int best_year, int max_alive);

int main(void) {
    int n;
    Event *events = NULL;

    printf("The Best Time to Be Alive Problem\n");
    get_data(&events, &n);

    // Sort events: primary by year, secondary: death (-1) before birth (+1)
    qsort(events, 2 * n, sizeof(Event), compare_events);

    int best_year = -1;
    int max_alive = 0;
    find_best_year(events, n, &best_year, &max_alive);

    display_results(best_year, max_alive);

    free(events);
    return 0;
}

// Comparator ensures deaths (-1) precede births (+1) if years are identical
int compare_events(const void *a, const void *b) {
    const Event *e1 = (const Event *)a;
    const Event *e2 = (const Event *)b;

    if (e1->year != e2->year) {
        return e1->year - e2->year;
    }
    return e1->type - e2->type;
}

// Read scientist life intervals and create event points
void get_data(Event **events, int *n) {
    printf("Enter number of scientists: ");
    while (scanf("%d", n) != 1 || *n <= 0) {
        printf("Invalid input! Please enter a positive integer: ");
        while (getchar() != '\n');
    }

    *events = (Event *)malloc(2 * (*n) * sizeof(Event));
    if (*events == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    printf("\nEnter birth and death years for each scientist (e.g., 1879 1955):\n");
    for (int i = 0; i < *n; i++) {
        int birth, death;
        printf("Scientist %d: ", i + 1);
        while (scanf("%d %d", &birth, &death) != 2 || birth > death) {
            printf("Invalid years! Ensure birth <= death. Re-enter: ");
            while (getchar() != '\n');
        }

        (*events)[2 * i].year = birth;
        (*events)[2 * i].type = 1;

        (*events)[2 * i + 1].year = death;
        (*events)[2 * i + 1].type = -1;
    }
    printf("\n");
}

// Linear sweep through events
void find_best_year(Event *events, int n, int *best_year, int *max_alive) {
    int current_alive = 0;
    *max_alive = 0;
    *best_year = -1;

    for (int i = 0; i < 2 * n; i++) {
        current_alive += events[i].type;
        if (current_alive > *max_alive) {
            *max_alive = current_alive;
            *best_year = events[i].year;
        }
    }
}

void display_results(int best_year, int max_alive) {
    printf("--- Timeline Analysis Results ---\n");
    printf("Year with Maximum Scientists Alive : %d\n", best_year);
    printf("Maximum Concurrent Scientists Alive: %d\n", max_alive);
}