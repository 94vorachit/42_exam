# `n_queens`

### Step 1 : Set Up

1. Input validation: Checks if exactly 2 arguments were provided (program name + n)
2. Conversion: Converts the argument to an integer using atoi()
3. Boundary check: Returns 0 if n ≤ 0 (invalid board size)
4. Memory allocation: Allocates space for n integers to store queen positions
5. Error handling: Checks if malloc succeeded

``` c
#include <stdlib.h>

int	main(int ac, char **av)
{
	int	n;
	int	*pos;
	
	if (ac != 2)
		return (1);
	n = atoi(av[1]);
	if (n <= 0)
		return (0);
	pos = malloc(sizeof(int) * n);
	if (!pos)
		return (1);
	.....
	return (0);
}
```

### Step 2 : Make utils function (ft_abs, ft_putnbr, ft_print_pos)

``` c
#include <unistd.h>

int	ft_abs(int x)
{
	if (x < 0)
		x *= -1;
	return (x);
}

void	ft_putnbr(int n)
{
	if (n >= 10)
		ft_putnbr(n / 10);
	char c = (n % 10) + '0';
	write(1, &c, 1);
}

void	ft_print_pos(int *pos, int n)
{
	int	i = 0;
	
	while (i < n)
	{
		ft_putnbr(pos[i]);
		if (i < n - 1)
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}
```

### Step 3 : Write function for checks whether a queen can be placed at (col, row).

``` c
// pos stores the row chosen for each column (pos[col] = row):
int ft_is_safe(int *pos, int col, int row)
{
	int	i = 0;
	
	while (i < col)
	{
		if (pos[i] == row) //Same row
			return (0);
		if (ft_abs(pos[i] - row) == col - i) // Same diagonal
			return (0);
		i++;
	}
	return (1);
}
```

### Step 4 : Write the function for solve.

The process is:
1. Try a row in the current column.
2. Check whether it is safe.
3. Store it in pos[col].
4. Recursively solve the next column.
5. If the next column cannot be solved, return and try another row.

This is backtracking. The function does not explicitly undo pos[col]; assigning a new value during the next attempt overwrites the old value.

``` c
void	ft_solve(int *pos, int n, int col)
{
	int	row = 0;

	while (row < n) //This recursively tries every row in the current column.
	{
		if (ft_is_safe(pos, col, row))
		{
			pos[col] = row;
			ft_solve(pos, n, col + 1);
		}
		row++;
	}
	if (col == n) //When all columns are filled:
		return (ft_print_pos(pos, n));
}
```

### Step 5 : Call solve function and free pos int main

``` c
int	main(int ac, char **av)
{
	.....
	ft_solve(pos, n, 0);
	free(pos);
	.....
}
```