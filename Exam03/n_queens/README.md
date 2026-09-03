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
}
```

### Step 1 : Solve 