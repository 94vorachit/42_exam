EXERCISE: POWERSET
DESCRIPTION: Find all subsets of a set of integers whose sum equals a target.
KEY CONCEPTS:
* 1. BACKTRACKING: Explore all possible combinations
* 2. SUBSET SUM: Classic subset sum problem
* 3. BINARY DECISION: For each element, include or exclude
* 4. ORDER PRESERVED: Elements must maintain their original order
ALGORITHM:
* 1. For each element, make two decisions: include or exclude
* 2. Keep current sum and current subset
* 3. If sum == target, print subset
* 4. Continue recursively with the remaining elements


STEP BY STEP
1. สร้าง int main(int ac, char **av) พร้อมดักเงื่อนไข
	1. argc == 1 : Return an error
		```c
		if (ac < 2>)
			return (1);
		```
	2. Special case: target = 0, print empty line and exit
		```c
		if (ac >= 2 && av[1][0] == '0 && av[1][1] == '\0')
		{
			printf("\n");
			return (0);
		}
		```
2. CHECK ARGUMENT VALIDATION :
	* Verify that all arguments are valid numbers
	* Allow negative numbers (starting with '-')
	* Allow positive numbers (optionally with '+')
	1. สร้าง function เพื่อตรวจเงื่อนไข args
	```c
	int ft_check_args(int ac, char **av)
	{
		int i = 1; // เริ่มที่ ac = 1
		while (i < ac)
		{
			int j = 0; // Skip initial sign if it exists
			if (av[i][j] == '+' || av[i][j] == '-')
				j++;
			while (av[i][j]) // Verify that the rest are digits
			{
				if (av[i][j] < '0' || av[i][j] > '9')
					return (0);
				j++;
			}
			i++;
		}
		return (1);
	}
	```
	2. เรียกใช้ function ที่สร้างใน main
	```c
	if (!ft_check_args(ac, av))
		return (1);
	```
3. กำหนดตัวแปลเพิ่ม
	1. target : ผลรวม (av[1])
	2. set_size : จำนวน input ทั้งหมดยกเว้น ./xxx กับ target
	3. *set : malloc ของ set_size
	4. *subset : malloc ของ set_size
	5. ดักเงื่อนไขกรณี set_size <= 0 และ malloc error : return error
	```c
	int target = atoi(av[1]);
	int set_size = ac - 2;
	if (set_size <= 0)
		return (1);
	int	*set = malloc(sizeof(int) * set_size);
	int	*subset = malloc (sizeof(int) * set_size);
	if (!set || !subset)
	{
		free(set);
		free(subset);
		return (1);
	}
	```
4. Fill the array with the numbers from the command : เริ่มที่ av[2]
	```c
	int	i = 0;
	int	j = 2;
	while (j < ac)
	{
		set[i] = atoi(av[j]);
		i++;
		j++;
	}
	``
5. สร้างตัวแปร found เพื่อใช้สำหรับพิมพ์ช่องว่าง(' ')ระหว่าง output
	```c
	int	found = 0;
	```
6. สร้าง Recursive backtracking function
	* PARAMETERS:
    	* set: Original array of numbers
    	* subset: Current array we are building
    	* set_size: Size of the original array
    	* subset_size: Current size of the subset
    	* index: Current position in the original array
    	* current_sum: Current sum of the subset
    	* target: Target sum
    	* found: Flag indicating whether a solution was found 
	* LOGIC: At each call, we have two options:
    	1. DO NOT include the current element (only advance the index)
			* We do not modify subset or current_sum
			* We only advance to the next element
    	2. DO include the current element (add it to the subset and update the sum)
			* Add element to subset
			* Update sum
			* Increment subset size
	```c
	void	ft_backtrack(int *set, int *subset, int set_size, int subset_size, int index, int current_sum, int target, int *found)
	{
		if (index == set_size)  // Base case: we have processed all elements
		{
			if (current_sum == target)
			{
				ft_print_subset(subset, subset_size)
				*found = 1;
			}
			return;
		}
		backtrack(set, subset, set_size, subset_size, index + 1, current_sum, target, found);
		subset[subset_size] = set[index];
		backtrack(set, subset, set_size, subset_size + 1, index + 1, current_sum + set[index], target, found);
	}
	```
7. สร้าง function ft_print_subset : OUTPUT FORMAT
    * If size == 0, print an empty line (empty subset)
    * Print elements separated by spaces
    * End with a newline
	```c
	void	ft_print_subset(int *subset, int size)
	{
		if (size == 0)
		{
			printf("\n");
			return;
		}
	
		int	i = 0;
		while (i < size)
		{
			if (i == size - 1)
				printf("%d", subset[i]);
			else
				printf("%d ", subset[i]);
			i++;
		}
		printf("\n");
	}
	```
8. เรียกใช้ function backtrack และ free set และ subset
	```c
	ft_backtrack(set, subset, set_size, 0, 0, 0, target, &found);
	free(set);
	free(subset);
	return (0);
	```