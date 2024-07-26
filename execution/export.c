/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:39:49 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/07/21 12:10:16 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_cmd(char **s, char *res, t_params *params)
{
	if (count_args(s) == 1)
	{
		if (ft_strchr(res, '='))
		{
			s[1] = ft_copy("");
			search_and_replace(ft_copy(s[0]), ft_copy(s[1]), &(params->env), 0);
			search_and_replace(s[0], s[1], &(params->sorted_env), 0);
		}
		else
			search_and_replace2(s[0], &(params->sorted_env));
		sort_env(params->sorted_env);
		free_update(s, params);
		return ;
	}
	if (params->export_f) //appending
		ft_join(s, params);
	search_and_replace(ft_copy(s[0]), ft_copy(s[1]), &(params->sorted_env), 0);
	search_and_replace(s[0], s[1], &(params->env), 0);
	sort_env(params->sorted_env);
	free_update(s, params);
}

void	search_and_replace(char *env, char *value, t_env **envi, int flag)
{
	t_env	*tmp;

	tmp = *envi;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, env))
		{
			if (!flag || flag == 3)
				free (env);
			if (tmp->value)
				free (tmp->value);
			tmp->value = value;
			return ;
		}
		tmp = tmp->next;
	}
	add_key(env, value, envi);
}

int	search_and_replace2(char *env, t_env **envi)
{
	t_env	*tmp;

	tmp = *envi;

	while (tmp)
	{
		if (!ft_strcmp(tmp->key, env))
		{
			free (env);
			return (1);
		}
		tmp = tmp->next;
	}
	add_key(env, NULL, envi);
	return (0);
}

void	add_key(char *key, char *value, t_env **env) //pass the head  of the list
{
	t_env	*new_key;

	new_key = malloc (sizeof(t_env));
	if (!new_key)
		return ; //more protection nega for this
	new_key->key = key;
	new_key->value = value;
	new_key->next = NULL;
	// if (!new_key->key || !new_key->value)
	// 	return ; //still thinking about this
	last_var((*env))->next = new_key;
}

char	*get_pwd(t_params *params)
{
	char	*pwd;

	pwd = malloc (1024);
	if (!pwd)
		return (NULL);
	if (!(getcwd(pwd, 1024)))
	{
		printf("cd: error retrieving current directory: getcwd\n");
		free (pwd);
		return (ft_strjoin2(get_key("PWD", params->env), "/.."));
	}
	return (pwd);
}
