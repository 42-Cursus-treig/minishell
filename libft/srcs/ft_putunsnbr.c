#include "libft.h"

int	ft_putunsnbr(unsigned int n)
{
	if (n <= 9)
		return (ft_putchar(n + '0'));
	else
		return (ft_putunsnbr(n / 10) + ft_putunsnbr(n % 10));
}
