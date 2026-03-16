#include "libft.h"

int	ft_putlowhexa(unsigned int n)
{
	if (n <= 9)
		return (ft_putchar(n + '0'));
	else if (n <= 16)
		return (ft_putchar(n - 10 + 'a'));
	else
		return (ft_putlowhexa(n / 16) + ft_putlowhexa(n % 16));
}
