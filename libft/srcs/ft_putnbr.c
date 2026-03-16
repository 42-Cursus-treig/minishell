#include "libft.h"

int	ft_putnbr(int n)
{
	long	nb;

	nb = n;
	if (n == INT_MIN)
		return (write(1, "-2147483648", 11));
	if (nb < 0)
	{
		nb = -nb;
		return (ft_putchar('-') + ft_putnbr(nb));
	}
	if (nb / 10)
	{
		return (ft_putnbr(nb / 10) + ft_putnbr(nb % 10));
	}
	else
		return (ft_putchar(nb + '0'));
}
