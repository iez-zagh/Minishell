/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:35:31 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/05/20 14:32:28 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*last_var(t_env *env_vars)
{
	t_env	*tmp;

	tmp = env_vars;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	add_var(t_env **env_vars, t_env *new)
{
	if (!*env_vars)
		*env_vars = new;
	else
	{
		last_var(*env_vars)->next = new;
	}
}

t_env	*set_env(char **env)
{
	t_env	*new_var;
	t_env	*var;
	int		start;
	int		end;
	int		i;
	int		j;

	i = 0;
	var = NULL;
	while(env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		start = j + 1;
		end = ft_strlen(env[i]);
		new_var = malloc(sizeof(t_env));
		new_var->key = ft_substr(env[i], 0, j);
		new_var->value = ft_substr(env[i], start, end - start);
		new_var->next = NULL;
		add_var(&var, new_var);
		i++;
	}
	return (var);
}

char	*ft_substr(const char *s, int start, int end)
{
	int		i;
	char	*res;

	i = 0;
	if (!s)
		return (NULL);
	res = malloc (end + 1);
	if (!res)
		return (NULL);
	while (s[start] && end > 0)
	{
		res[i++] = s[start++];
		end--;
	}
	res[i] = '\0';
	return (res);
}
