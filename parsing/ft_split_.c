/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:00:13 by houamrha          #+#    #+#             */
/*   Updated: 2024/07/30 11:00:17 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	words_count(char const *s, char c, int *still)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == c || s[i] == '\t' || s[i] == '\n'))
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] && s[i] != c && s[i] != '\t' && s[i] != '\n')
			i++;
	}
	if (is_white(s[i - 1]))
		*still = 1;
	else
		*still = 0;
	return (count);
}

static char	*ft_cpy(char const *str, char c)
{
	char	*copy;
	int		w_len;
	int		i;

	i = 0;
	w_len = 0;
	while (*str && *str != c && *str != '\t' && *str != '\n')
	{
		str++;
		w_len++;
	}
	str -= w_len;
	copy = ft_malloc((w_len + 1) * sizeof(char), 1);
	if (copy == NULL)
		return (NULL);
	while (i < w_len)
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

static char	**allocate_and_initialize_array(const char *s, char c, int w_count)
{
	char	**array;
	int		i;

	array = ft_malloc((w_count + 1) * sizeof(char *), 1);
	if (array == NULL)
		return (NULL);
	i = 0;
	while (i < w_count)
	{
		while (*s == c || *s == '\t' || *s == '\n')
			s++;
		array[i] = ft_cpy(s, c);
		if (array[i] == NULL)
			return (NULL);
		i++;
		while (*s && *s != c && *s != '\t' && *s != '\n')
			s++;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_mysplit(char const *s, char c, int *still)
{
	int		w_count;
	char	**array;

	if (!s)
		return (NULL);
	w_count = words_count(s, c, still);
	array = allocate_and_initialize_array(s, c, w_count);
	return (array);
}
