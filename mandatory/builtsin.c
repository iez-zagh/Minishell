/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtsin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 20:05:53 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/05/15 13:21:09 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_env(char *s1, char *s2)
{
	char	*join_string;
	char	*join;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	join_string = (char *)malloc
		((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (!join_string)
		return (0);
	join = join_string;
	while (*s1)
	{
		*join = *s1;
		join++;
		s1++;
	}
	*join = '=';
    join++;
	while (*s2)
	{
		*join = *s2;
		join++;
		s2++;
	}
	*join = '\0';
	return (join_string);
}

char	*get_home(t_env *env)
{
	while (env)
	{
		if (!(ft_strcmp("HOME", env->key)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*ft_copy(const char *s)
{
	int		i;
	char	*res;

	if (!s)
		return (NULL);
	i = 0;
	res = malloc (ft_strlen(s) + 1);
	if (!res)
		return (NULL);
	while (s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
	
}
