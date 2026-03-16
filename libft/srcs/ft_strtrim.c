#include "libft.h"

static int	ft_is_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_strndup(char const *s, size_t n)
{
	char	*ptr;
	size_t	i;

	ptr = malloc(sizeof(char) * (n + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	if (!s1[0])
		return (ft_strndup("", 0));
	len = ft_strlen(s1);
	start = 0;
	while (s1[start] && ft_is_in_set(s1[start], set))
		start++;
	if (start == len)
		return (ft_strndup("", 0));
	end = len - 1;
	while (end > start && ft_is_in_set(s1[end], set))
		end--;
	return (ft_strndup(s1 + start, end - start + 1));
}
/*
int	main(int argc, char *argv[])
{
	char	*s1;
	char	*set;
	char	*result;

	if (argc != 3)
	{
		printf("Usage: %s [string] [set]\n", argv[0]);
		return (1);
	}
	s1 = argv[1];
	set = argv[2];
	result = ft_strtrim(s1, set);
	printf("Result: \"%s\"\n", result);
	free(result);
	return (0);
}
*/