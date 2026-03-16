#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	ch;
	size_t	i;

	ch = (char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ch)
			return ((char *)&s[i]);
		i++;
	}
	if (ch == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
/*
int	main(int argc, char *argv[])
{
	char	*result;
	char	*str;
	char	character;

	if (argc != 3)
	{
		printf("Usage: %s [str] [char]\n", argv[0]);
		return (1);
	}
	str = argv[1];
	character = argv[2][0];
	result = ft_strchr(str, character);
	if (result)
		printf("Substring found: \"%s\"\n", result);
	else
		printf("Character not found\n");
	return (0);
}
*/