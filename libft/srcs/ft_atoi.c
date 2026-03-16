#include "libft.h"

int	ft_atoi(const char *str)
{
	int		nbr;
	int		sign;
	size_t	i;

	nbr = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || ('\t' <= str[i] && str[i] <= '\r'))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		nbr = (nbr * 10) + (str[i] - '0');
		i++;
	}
	return (nbr * sign);
}

/*
int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s [str]\n", argv[0]);
		return (1);
	}
	printf("String converted in int is %d\n", ft_atoi(argv[1]));
	return (0);
}
*/