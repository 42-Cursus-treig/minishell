#include "libft.h"

static int	is_separator(char ch, char c)
{
	return (ch == c);
}

static int	count_words(char const *str, char c)
{
	int	i;
	int	count;
	int	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (str[i])
	{
		if (!is_separator(str[i], c) && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (is_separator(str[i], c))
			in_word = 0;
		i++;
	}
	return (count);
}

static char	*word_splitter(char const *str, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (str[i] && !is_separator(str[i], c))
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (str[i] && !is_separator(str[i], c))
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	int		j;

	result = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && j < count_words(s, c))
	{
		if (!is_separator(s[i], c))
		{
			result[j] = word_splitter(&s[i], c);
			if (!result[j])
				return (NULL);
			while (s[i] && !is_separator(s[i], c))
				i++;
			j++;
		}
		else
			i++;
	}
	result[j] = NULL;
	return (result);
}
/*
int	main(int argc, char *argv[])
{
	char	**result;
	char	*str;
	char	separator;
	int		i;

	if (argc != 3)
	{
		printf("Usage: %s [str] [char]\n", argv[0]);
		return (1);
	}
	str = argv[1];
	separator = argv[2][0];
	result = ft_split(str, separator);
	i = 0;
	while (result[i])
	{
		printf("Element %d: %s\n", i, result[i]);
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
}
*/