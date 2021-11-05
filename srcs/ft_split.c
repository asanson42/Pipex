#include "pipex.h"

static int	ft_countwords(char const *s1, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s1[i])
	{
		while (s1[i] && s1[i] == c)
			i++;
		if (s1[i] && (!(s1[i] == c)))
			count++;
		while (s1[i] && s1[i] != c)
			i++;
	}
	return (count);
}

static int	ft_sizeword(char const *s, char c, int i)
{
	int	size;

	size = 0;
	while (s[i] && s[i] != c)
	{
		size++;
		i++;
	}
	return (size);
}

char	**ft_free(char **strs, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		index;
	int		i;
	int		j;

	i = 0;
	index = 0;
	if (!s)
		return (NULL);
	strs = malloc(sizeof(char *) * (ft_countwords(s, c) + 1));
	while (s[i] && (index < ft_countwords(s, c)))
	{
		while (s[i] == c)
			i++;
		strs[index] = malloc(sizeof(char) * ft_sizeword(s, c, i) + 1);
		if (!strs[index])
			return (ft_free(strs, index));
		j = 0;
		while (s[i] && s[i] != c)
			strs[index][j++] = s[i++];
		strs[index][j] = '\0';
		index++;
	}
	strs[index] = 0;
	return (strs);
}
