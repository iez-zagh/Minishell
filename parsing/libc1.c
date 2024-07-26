#include "../minishell.h"

char	*ft_strdup(const char *s1)
{
	char		*copy;
	char		*c;
	const char	*s;
	int			i;

	i = 0;
	s = s1;
	while (*s)
	{
		i++;
		s++;
	}
	copy = ft_malloc(i * sizeof(char) + 1, 1);
	if (copy == NULL)
		return (0);
	c = copy;
	while (*s1)
	{
		*c = *s1;
		c++;
		s1++;
	}
	*c = '\0';
	return (copy);
}

char	*ft_mysubstr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	int		i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	i = 0;
	substring = ft_malloc((len + 1) * sizeof(char), 1);
	if (substring == 0)
		return (NULL);
	while (len > 0)
	{
		substring[i] = s[start];
		i++;
		start++;
		len--;
	}
	substring[i] = '\0';
	return (substring);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i]) // added
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join_string;
	char	*join;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (!s1)
		s1 = ft_strdup("");
	join_string = ft_malloc
		((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char), 1);
	if (join_string == 0)
		return (0);
	join = join_string;
	while (*s1)
	{
		*join = *s1;
		join++;
		s1++;
	}
	while (*s2)
	{
		*join = *s2;
		join++;
		s2++;
	}
	*join = '\0';
	return (join_string);
}

int	ft_strcmp(char *s1, char *s2)
{
	if (!s2 || !s1)
		return (1);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}