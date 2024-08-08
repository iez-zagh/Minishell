/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:00:48 by houamrha          #+#    #+#             */
/*   Updated: 2024/08/01 11:33:28 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*fmysubstr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	int		i;

	if (!s)
		return (NULL);
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
	while (s && s[i])
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
	return (*join = '\0', join_string);
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
