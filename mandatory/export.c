/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:39:49 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/05/22 16:29:22 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_cmd(t_parse *st)
{
	char	**res;

	if (count_args(st->com_arr) == 1) //handle the "export" yooo i am here
	{
		just_export(st);
		return ;
	}
	if (count_args(st->com_arr) > 2)
		return ;
	check_join(st);
	res = ft_split(st->com_arr [1], '=');
	if (st->export_f)
		ft_join(res,st);
	search_and_replace(ft_copy(res[0]), ft_copy(res[1]), &(st->sorted_env), 0);
	search_and_replace(res[0], res[1], &(st->env), 0);
	free (res);
	ft_free(st->env2);
	st->env2= list2array(st->env, st);
	free(st->path);
	st->path = ft_copy(get_key("PATH", st->env)); //handle empty path or else
	ft_free(st->paths_array);
	st->paths_array = ft_split(st->path, ':');
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
			free (tmp->value);
			tmp->value = value;
			return ;
		}
		tmp = tmp->next;
	}
	add_key(env, value, envi);
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

void	check_join(t_parse *st)
{
	int	i;

	i = 0;
	st->export_f = 0;
	while (st->com_arr[1][i])
	{
		if (st->com_arr[1][i] == '=')
			if (st->com_arr[1][i - 1] == '+')
			{
				st->export_f = 1;
				ft_join_value(st);
			}
		i++;
	}
}

void	ft_join_value(t_parse *st)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc (ft_strlen(st->com_arr[1]));
	if (!res)
		error(st, 2); //more portection
	while (st->com_arr[1][i])
	{
		if (st->com_arr[1][i] == '+')
		{
			i++;
			continue;
		}
		res[j++] = st->com_arr[1][i++];
	}
	res[j] = '\0';
	free(st->com_arr[1]);
	st->com_arr[1] = res;
}