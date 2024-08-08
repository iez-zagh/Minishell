/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 20:05:53 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/06 21:37:31 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_allocate(char *s1, char *s2)
{
	char	*s;

	if (!s1 || !s2)
		return (NULL);
	s = malloc((ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!s)
		return (NULL);
	return (s);
}

char	*ft_strjoin_env(char *s1, char *s2, t_params *params)
{
	char	*join_string;
	char	*join;

	join_string = check_allocate(s1, s2);
	if (!join_string)
		malloc_error(params);
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

char	*get_key(char *s, t_env *env)
{
	while (env)
	{
		if (!(ft_strcmp(s, env->key)))
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

char	*ft_slashs(t_parse *st)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (st->cmd[0][i])
	{
		if (st->cmd[0][i] == '/')
			j = i + 1;
		i++;
	}
	return (ft_substr(st->cmd[0], j, i - 1));
}
