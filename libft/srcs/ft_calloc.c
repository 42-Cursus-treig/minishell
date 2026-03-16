#include "libft.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*ptr;
	size_t	i;
	size_t	size;

	if (nelem == 0 || elsize == 0)
		return (malloc(0));
	size = nelem * elsize;
	ptr = (void *)malloc(nelem * elsize);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		*(unsigned char *)(ptr + i) = 0;
		i++;
	}
	return (ptr);
}
/*
int	main(int argc, char *argv[])
{
	size_t			nelem;
	size_t			elsize;
	size_t			i;
	void			*ptr;
	unsigned char	*buffer;

	if (argc != 3)
	{
		printf("Usage: %s [nelem] [elsize]\n", argv[0]);
		return (1);
	}
	nelem = (size_t)atoi(argv[1]);
	elsize = (size_t)atoi(argv[2]);
	ptr = ft_calloc(nelem, elsize);
	if (!ptr)
	{
		printf("Erreur d'allocation mémoire\n");
		return (1);
	}
	buffer = (unsigned char *)ptr;
	i = 0;
	printf("Premiers octets: [");
	while (i < (nelem * elsize) && i < 10)
	{
		if (i > 0)
			printf(" ");
		printf("0x%02x", buffer[i]);
		i++;
	}
	if ((nelem * elsize) > 10)
		printf(" ...");
	printf("]\n");
	free(ptr);
	return (0);
}
*/