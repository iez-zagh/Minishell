/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:49:28 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/05/15 10:56:37 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	words_count(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == c || s[i] == '\t'))
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] && s[i] != c && s[i] != '\t')
			i++;
	}
	return (count);
}

char	*ft_cpy(char const *str, char c)
{
	char	*copy;
	int		w_len;
	int		i;

	i = 0;
	w_len = 0;
	while (*str && *str != c && *str != '\t')
	{
		str++;
		w_len++;
	}
	str -= w_len;
	copy = (char *)malloc((w_len + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	while (i < w_len)
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
	}
	free(array);
}

char	**allocate_and_initialize_array(const char *s, char c, int w_count)
{
	char	**array;
	int		i;

	array = (char **)malloc((w_count + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	i = 0;
	while (i < w_count)
	{
		while (*s == c || *s == '\t')
			s++;
		array[i] = ft_cpy(s, c);
		if (array[i] == NULL)
		{
			free_array(array);
			return (NULL);
		}
		i++;
		while (*s && *s != c && *s != '\t')
			s++;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	int		w_count;
	char	**array;

	if (!s)
		return (NULL);
	w_count = words_count(s, c);
	array = allocate_and_initialize_array(s, c, w_count);
	return (array);
}
