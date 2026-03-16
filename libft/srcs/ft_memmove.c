#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	long	i;

	if (dest < src)
	{
		i = 0;
		while ((size_t)i < n)
		{
			*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
			i++;
		}
	}
	else
	{
		i = n - 1;
		while (i >= 0)
		{
			*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
			i--;
		}
	}
	return (dest);
}
/*
int	main(int argc, char *argv[])
{
	char	*str;
	size_t	n;
	size_t	offset;

	if (argc != 4)
	{
		printf("Usage: %s [str] [offset] [n]\n", argv[0]);
		return (1);
	}
	str = malloc(sizeof(char) * (strlen(argv[1]) + 1));
	offset = (size_t)atoi(argv[2]);
	n = (size_t)atoi(argv[3]);
	if (!str)
		return (1);
	strcpy(str, argv[1]);
	printf("Before ft_memmove : %s\n", str);
	ft_memmove(str, str + offset, n);
	printf("After ft_memmove : %s\n", str);
	free(str);
	return (0);
}
*/