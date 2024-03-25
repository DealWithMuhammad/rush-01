#include <unistd.h>
#include <stdlib.h>

#define N 4

// Function to check if a number can be placed at grid[row][col]
int isSafe(int grid[N][N], int row, int col, int num) {
    int x = 0;
    while (x < N) {
        if (grid[row][x] == num || grid[x][col] == num) {
            return 0;
        }
        x++;
    }
    return 1;
}

// Function to print the grid
void printGrid(int grid[N][N]) {
    char output[3];
    int row = 0;
    while (row < N) {
        int col = 0;
        while (col < N) {
            output[0] = '0' + grid[row][col];
            output[1] = ' ';
            output[2] = '\0';
            write(1, output, 2); // Write number and space
            col++;
        }
        write(1, "\n", 1); // Write newline
        row++;
    }
}

// Recursive function to solve the Skyscraper puzzle
int solveSkyscraper(int grid[N][N], int row, int col) {
    if (row == N - 1 && col == N) {
        return 1;
    }
    if (col == N) {
        row++;
        col = 0;
    }
    if (grid[row][col] > 0) {
        return solveSkyscraper(grid, row, col + 1);
    }
    int num = 1;
    while (num <= N) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSkyscraper(grid, row, col + 1)) {
                return 1;
            }
            grid[row][col] = 0; // Backtrack
        }
        num++;
    }
    return 0; // No solution found
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        write(1, "Usage: ./rush-01 \"16-digit input\"\n", 34);
        return 1;
    }

    int grid[N][N] = {0};
    int clues[4 * N];
    int i = 0;
    while (i < 4 * N) {
        if (argv[1][i] >= '1' && argv[1][i] <= '4') {
            clues[i] = argv[1][i] - '0';
        } else {
            write(1, "Invalid input\n", 14);
            return 1;
        }
        i++;
    }

    if (!solveSkyscraper(grid, 0, 0)) {
        write(1, "No solution exists\n", 18);
        return 0;
    }
    printGrid(grid);
    return 0;
}

