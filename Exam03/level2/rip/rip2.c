#include <unistd.h>

static int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static void	print_result(char *s)
{
	int	len;

	len = ft_strlen(s);
	write(1, s, len);
	write(1, "\n", 1);
}

static int	min_removals_needed(char *s)
{
	int	balance;
	int	removals;
	int	i;

	balance = 0;
	removals = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '(')
			balance++;
		else if (balance > 0)
			balance--;
		else
			removals++;
		i++;
	}
	removals += balance;
	return (removals);
}

static void	backtrack(char *s, int index, int open, int removed, int target)
{
	if (index == (int)ft_strlen(s))
	{
		if (open == 0 && removed == target)
			print_result(s);
		return ;
	}
	if (s[index] == '(')
	{
		backtrack(s, index + 1, open + 1, removed, target);
		if (removed < target)
		{
			s[index] = ' ';
			backtrack(s, index + 1, open, removed + 1, target);
			s[index] = '(';
		}
	}
	else
	{
		if (open > 0)
			backtrack(s, index + 1, open - 1, removed, target);
		if (removed < target)
		{
			s[index] = ' ';
			backtrack(s, index + 1, open, removed + 1, target);
			s[index] = ')';
		}
	}
}

int	main(int argc, char **argv)
{
	char	*str;
	int		target;
	int		i;

	if (argc != 2)
		return (1);
	i = 0;
	while (argv[1][i])
	{
		if (argv[1][i] != '(' && argv[1][i] != ')')
			return (1);
		i++;
	}
	str = argv[1];
	target = min_removals_needed(str);
	backtrack(str, 0, 0, 0, target);
	return (0);
}
