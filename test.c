#include <unistd.h>
#include <stdlib.h>

#define N 4

int isSafe(int *grid, int row, int col, int num)
{
    int x = 0;
    // Check the row for the same number
    while (x < N)
    {
        if (*(grid + row*N + x) == num)
            return 0;
        x++;
    }
    x = 0; // Reset x to 0 to check the column
    // Check the column for the same number
    while (x < N)
    {
        if (*(grid + x*N + col) == num)
            return 0;
        x++;
    }
    return 1; // Return 1 if no conflicts are found
}

// Function to print the grid
void	printGrid(int *grid)
{
	char output[2];
	int row = 0;
	while(row < N)
	{
		int	col = 0;
		while	(col < N) 
		{
            output[0] = '0' + *(grid + row*N + col);
            output[1] = ' ';
            write(1, output, 2);
			col++;
        }
        write(1, "\n", 1);
		row++;
    }
}

// Function to solve the puzzle using backtracking
int	solveSkyscraper(int *grid, int row, int col)
{
    if (row == N - 1 && col == N)
        return 1;
    if (col == N)
	{
        row++;
        col = 0;
    }
    if (*(grid + row*N + col) > 0)
        return solveSkyscraper(grid, row, col + 1);
	int num = 1;
	while (num <= N)
		{
			if (isSafe(grid, row, col, num) == 1)
			{
            *(grid + row*N + col) = num;
            if (solveSkyscraper(grid, row, col + 1) == 1)
                return 1;
			}
			*(grid + row*N + col) = 0;
			num++;
		}
		return 0;
}

int main()
{
	int *grid = malloc(N * N * sizeof(int));
	int	i = 0;
	while (i < N*N)
	{
		*(grid + i) = 0;
		i++;
	}
    int *clues = malloc(4 * N * sizeof(int));
    char buffer[2];
	while (i < 4*N)
	{
        read(0, buffer, 2);
        *(clues + i) = buffer[0] - '0';
    	i++;
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
