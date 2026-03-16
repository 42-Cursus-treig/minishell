#include "libft.h"

static int	convert(const char *c, int *i, va_list *arg_list)
{
	*i = *i + 1;
	if (*(c + 1) == 'c')
		return (ft_putchar(va_arg(*arg_list, int)));
	else if (*(c + 1) == 'd' || *(c + 1) == 'i')
		return (ft_putnbr(va_arg(*arg_list, int)));
	else if (*(c + 1) == 's')
		return (ft_putstr(va_arg(*arg_list, char *)));
	else if (*(c + 1) == 'p')
		return (ft_putadress(va_arg(*arg_list, void *)));
	else if (*(c + 1) == 'u')
		return (ft_putunsnbr(va_arg(*arg_list, unsigned int)));
	else if (*(c + 1) == 'x')
		return (ft_putlowhexa(va_arg(*arg_list, unsigned int)));
	else if (*(c + 1) == 'X')
		return (ft_puthighhexa(va_arg(*arg_list, unsigned int)));
	else if (*(c + 1) == '%')
		return (ft_putchar('%'));
	else
	{
		ft_putchar('%');
		*i = *i - 1;
		return (1);
	}
}

int	ft_printf(const char *format, ...)
{
	int		tmp;
	int		len;
	int		i;
	va_list	arg_list;

	if (!format)
		return (-1);
	i = 0;
	len = 0;
	va_start(arg_list, format);
	while (format[i])
	{
		if (format[i] == '%')
			tmp = convert(format + i, &i, &arg_list);
		else
			tmp = ft_putchar(format[i]);
		len += tmp;
		i++;
	}
	va_end(arg_list);
	return (len);
}
