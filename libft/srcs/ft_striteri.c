#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		(*f)(i, s + i);
		i++;
	}
}
/*
void	to_upper_even(unsigned int i, char *c)
{
	int	j;

	j = 0;
	if (i % 2 == 0 && c[j] >= 'a' && c[j] <= 'z')
	{
		c[j] = c[j] - 32;
		j++;
	}
}

int	main(int argc, char *argv[])
{
	char	*str;

	if (argc != 2)
	{
		printf("Usage: %s [str]\n", argv[0]);
		return (1);
	}
	str = argv[1];
	ft_striteri(str, to_upper_even);
	printf("Result: \"%s\"\n", str);
	return (0);
}
*/