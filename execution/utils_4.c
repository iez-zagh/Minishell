/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:22:49 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/06 22:55:16 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strchr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_join_value(char **s)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = ft_malloc(ft_strlen(*s), 1);
	if (!res)
	{
		perror("malloc");
		return ;
	}
	while ((*s)[i])
	{
		if ((*s)[i] == '+')
		{
			i++;
			continue ;
		}
		res[j++] = (*s)[i++];
	}
	res[j] = '\0';
	*s = res;
}

void	check_join(char **s, t_parse *st, t_params *params)
{
	int	i;

	(void)st;
	i = 0;
	params->export_f = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == '+')
		{
			if ((*s)[i + 1] && (*s)[i + 1] == '=')
			{
				params->export_f = 1;
				ft_join_value(s);
				return ;
			}
		}
		i++;
	}
}

void	free_update(char **res, t_params *params)
{
	(void)res;
	ft_free(params->env2);
	params->env2 = list2array(params->env, params);
	free(params->path);
	params->path = ft_copy(get_key("PATH", params->env));
	ft_free(params->paths_array);
	if (!params->path)
	{
		params->paths_array = NULL;
		return ;
	}
	params->paths_array = ft_split(params->path, ':');
}

char	**export_checker2(char **res, char *s, int i)
{
	int	j;

	j = 0;
	if (i < (int)ft_strlen(s))
	{
		res[1] = ft_malloc(ft_strlen(&s[i]) + 1, 1);
		while (s[i])
			res[1][j++] = s[i++];
		res[1][j] = '\0';
		res[2] = NULL;
	}
	else
		res[1] = NULL;
	return (res);
}
