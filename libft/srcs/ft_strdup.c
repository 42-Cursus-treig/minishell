#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		i;

	ptr = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
/*
int	main(int argc, char *argv[])
{
	char	*dup;
	char	*str;

	if (argc != 2)
	{
		printf("Usage: %s [str]\n", argv[0]);
		return (1);
	}
	str = argv[1];
	dup = ft_strdup(str);
	printf("%s\n", dup);
	free(dup);
	return (0);
}
*/