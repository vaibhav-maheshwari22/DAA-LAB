#include <stdio.h>

// Recursive function
void solve_toh(int n, char source, char destination, char auxiliary, long long *moves) {

    if (n == 1) {
        (*moves)++;
        return;
    }

    solve_toh(n - 1, source, auxiliary, destination, moves);

    // Record the move for the nth disc
    (*moves)++;

    solve_toh(n - 1, auxiliary, destination, source, moves);

}

int main() {

    FILE *fp = fopen("q4_data.csv", "w");

    if (fp == NULL) return 1;

    fprintf(fp, "n,total_moves\n");

    // Calculate moves
    for (int i = 1; i <= 15; i++) {
        long long moves = 0;

        // 'A' is source, 'C' is destination, 'B' is auxiliary
        solve_toh(i, 'A', 'C', 'B', &moves);
        fprintf(fp, "%d,%lld\n", i, moves);
    }
    
    fclose(fp);
    printf("Data successfully written to q4_data.csv\n");

    return 0;
}
