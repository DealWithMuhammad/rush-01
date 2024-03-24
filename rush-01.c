#include <unistd.h>
#include <stdlib.h>

#define N 4

// Function to check if a number can be placed at the given position
int isSafe(int grid, int row, int col, int num)
{
    for (int x = 0; x <= 3; x++)
        if ((grid + rowN + x) == num)
            return 0;
    for (int x = 0; x <= 3; x++)
        if ((grid + xN + col) == num)
            return 0;
    return 1;
}

// Function to print the grid
void printGrid(intgrid)
{
    char output[2];
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            output[0] = '0' + (grid + rowN + col);
            output[1] = ' ';
            write(1, output, 2);
        }
        write(1, "\n", 1);
    }
}

// Function to solve the puzzle using backtracking
int solveSkyscraper(int grid, int row, int col)
{
    if (row == N - 1 && col == N)
        return 1;
    if (col == N)
    {
        row++;
        col = 0;
    }
    if ((grid + row * N + col) > 0)
        return solveSkyscraper(grid, row, col + 1);
    for (int num = 1; num <= N; num++)
    {
        if (isSafe(grid, row, col, num) == 1)
        {
            (grid + rowN + col) = num;
            if (solveSkyscraper(grid, row, col + 1) == 1)
                return 1;
        }
        (grid + rowN + col) = 0;
    }
    return 0;
}

int main(int argc, char argv[])
{
    intgrid = malloc(N * N * sizeof(int));
    for (int i = 0; i < N * N; i++)
        (grid + i) = 0;

    // Add code to take clues as input from the user
    intclues = malloc(4 * N * sizeof(int));
    char buffer[2];
    for (int i = 0; i < 4 * N; i++)
    {
        read(0, buffer, 2);
        *(clues + i) = buffer[0] - '0';
    }

    if (solveSkyscraper(grid, 0, 0) == 0)
    {
        write(1, "No solution exists\n", 18);
        free(grid);
        free(clues);
        return 0;
    }
    printGrid(grid);
    free(grid);
    free(clues);
    return 0;
}