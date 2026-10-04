/*
 * Description: O(n) algorithm to sort items by color (Red, Blue, Yellow) 
 * while maintaining the sorted order of numbers (Stable Sort).
 */

#include <stdio.h>
#include <stdlib.h>

// Using enum for colors makes the code easier to read
typedef enum { RED = 0, BLUE = 1, YELLOW = 2 } Color;

// Struct 
typedef struct {
    int val;
    Color col;
} Item;

void sort_colors(Item *arr, int n);
void get_data(Item *arr, int n);
void display(Item *arr, int n, char *msg);
char* get_color_name(Color c);

int main() {
    int n;

    printf("Stable Color Sort\n");
    printf("-----------------\n");
    printf("Enter number of items: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size!\n");
        return 1;
    }

    // Dynamically allocate memory
    Item *arr = (Item *)malloc(n * sizeof(Item));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Take input from the user
    get_data(arr, n);
    display(arr, n, "Initial Array");

    // Perform the O(n) stable sort
    sort_colors(arr, n);

    display(arr, n, "Final Sorted Array");

    // Free the allocated memory 
    free(arr);
    return 0;
}

// O(n) sorting logic using separate buckets to maintain stability
void sort_colors(Item *arr, int n) {
    // Create temporary arrays for each color
    Item *reds = (Item *)malloc(n * sizeof(Item));
    Item *blues = (Item *)malloc(n * sizeof(Item));
    Item *yellows = (Item *)malloc(n * sizeof(Item));

    if (reds == NULL || blues == NULL || yellows == NULL) {
        printf("Memory error during sorting!\n");
        exit(1);
    }

    int r = 0, b = 0, y = 0;

    // Traverse the original array and push items into their respective buckets
    for (int i = 0; i < n; i++) {
        if (arr[i].col == RED) {
            reds[r++] = arr[i];
        } else if (arr[i].col == BLUE) {
            blues[b++] = arr[i];
        } else {
            yellows[y++] = arr[i];
        }
    }

    // Reconstruct the original array by placing Reds, then Blues, then Yellows
    int idx = 0;
    for (int i = 0; i < r; i++) arr[idx++] = reds[i];
    for (int i = 0; i < b; i++) arr[idx++] = blues[i];
    for (int i = 0; i < y; i++) arr[idx++] = yellows[i];

    // Clean up temporary buckets
    free(reds);
    free(blues);
    free(yellows);
}

//  user input
void get_data(Item *arr, int n) {
    printf("\nEnter data (Number and Color Code [0=Red, 1=Blue, 2=Yellow]):\n");
    printf("Make sure the numbers are entered in sorted order!\n");
    
    for (int i = 0; i < n; i++) {
        int num, c;
        printf("Item %d: ", i + 1);
        scanf("%d %d", &num, &c);
        arr[i].val = num;
        arr[i].col = (Color)c;
    }
    printf("\n");
}

// print color names instead of integers
char* get_color_name(Color c) {
    if (c == RED) return "Red";
    if (c == BLUE) return "Blue";
    if (c == YELLOW) return "Yellow";
    return "Unknown";
}

// print the array contents
void display(Item *arr, int n, char *msg) {
    printf("--- %s ---\n", msg);
    for (int i = 0; i < n; i++) {
        printf("[%d, %s] ", arr[i].val, get_color_name(arr[i].col));
        
        if ((i + 1) % 5 == 0) printf("\n"); 
    }
    printf("\n\n");
}