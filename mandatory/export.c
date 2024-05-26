/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:39:49 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/05/26 15:53:13 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_cmd(t_parse *st, char **s, char *res)
{
	if (count_args(s) == 1)
	{
		if (ft_strchr(res, '='))
		{
			s[1] = ft_copy("");
			search_and_replace(ft_copy(s[0]), ft_copy(s[1]), &(st->env), 0);
			search_and_replace(s[0], s[1], &(st->sorted_env), 0);
		}
		search_and_replace2(s[0], &(st->sorted_env));
		free_update(s, st);
		return ;
	}
	if (st->export_f)
		ft_join(s,st);
	search_and_replace(ft_copy(s[0]), ft_copy(s[1]), &(st->sorted_env), 0);
	search_and_replace(s[0], s[1], &(st->env), 0);
	free_update(s, st);
}

void	search_and_replace(char *env, char *value, t_env **envi, int flag)
{
	t_env	*tmp;

	tmp = *envi;

	while (tmp)
	{
		if (!ft_strcmp(tmp->key, env))
		{
			if (!flag)
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

void	search_and_replace2(char *env, t_env **envi)
{
	t_env	*tmp;

	tmp = *envi;

	while (tmp)
	{
		if (!ft_strcmp(tmp->key, env))
			return ;
		tmp = tmp->next;
	}
	add_key(env, NULL, envi);
}

void	add_key(char *key, char *value, t_env **env) //pass the head  of the list
{
	t_env	*new_key;

	new_key = malloc (sizeof(t_env));
	if (!new_key)
		return ;//more protection nega for this
	new_key->key = key;	
	new_key->value = value;
	new_key->next = NULL;
	// if (!new_key->key || !new_key->value)
	// 	return ; //still thinking about this
	last_var((*env))->next = new_key;
}

char	*get_pwd(t_parse *st)
{
	char	*pwd;

	pwd = malloc (1024);
	if (!pwd)
		return (NULL);
	if (!(getcwd(pwd, 1024)))
	{
		printf("getcwd() error\n");
		freeing(st);
		exit (1);
	}
	return (pwd);
}
