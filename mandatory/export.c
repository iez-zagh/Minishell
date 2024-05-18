/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:39:49 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/05/18 15:52:05 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_cmd(t_parse *st)
{
	char	**res;

	if (count_args(st->com_arr) == 1) //handle the "export" yooo i am here
		return ;
	res = ft_split(st->com_arr[1], '=');
	search_and_replace(res[0], res[1], &st, 0);
	free (res);
	ft_free(st->env2);
	list2array(st->env, st);
	free(st->path);
	st->path = ft_copy(get_key("PATH", st->env)); //handle empty path or else
	ft_free(st->paths_array);
	st->paths_array = ft_split(st->path, ':');
}

void	search_and_replace(char *env, char *value, t_parse **st, int flag)
{
	t_env	*tmp;

	tmp = (*st)->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, env))
		{
			free (tmp->value);
			if (!flag)
				free (env);
			tmp->value = value;
			return ;
		}
		tmp = tmp->next;
	}
	add_key(env, value, st);
}

void	add_key(char *key, char *value, t_parse **st) //pass the head  of the list
{
	t_env	*new_key;

	new_key = malloc (sizeof(t_env));
	if (!new_key)
		return ;//more protection nega
	new_key->next = NULL;
	new_key->key = key;
	new_key->value = value;
	if (!new_key->key || !new_key->value)
		return ;
	last_var((*st)->env)->next = new_key;
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