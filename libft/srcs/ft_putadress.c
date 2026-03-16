#include "libft.h"

static int	print_hex(unsigned long n)
{
	char	res[16];
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (n == 0)
		res[i++] = '0';
	else
	{
		while (n > 0)
		{
			if (n % 16 < 10)
				res[i++] = (n % 16) + '0';
			else
				res[i++] = (n % 16) - 10 + 'a';
			n /= 16;
		}
	}
	while (--i >= 0)
	{
		ft_putchar(res[i]);
		count++;
	}
	return (count);
}

int	ft_putadress(void *adress)
{
	if (!adress)
		return (ft_putstr("(nil)"));
	ft_putstr("0x");
	return (2 + print_hex((unsigned long) adress));
}
