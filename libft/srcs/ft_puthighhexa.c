#include "libft.h"

int	ft_puthighhexa(unsigned int n)
{
	if (n <= 9)
		return (ft_putchar(n + '0'));
	else if (n <= 16)
		return (ft_putchar(n - 10 + 'A'));
	else
		return (ft_puthighhexa(n / 16) + ft_puthighhexa(n % 16));
}
