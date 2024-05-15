/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:39:49 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/05/15 18:44:03 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_cmd(t_parse *st)
{
	char	**res;

	if (count_args(st->com_arr) == 1) //handle the "export"
		return ;
	res = ft_split(st->com_arr[1], '=');
	search_and_replace(res[0], res[1], st);
	ft_free(st->env2);
	list2array(st->env, st);
}

void	search_and_replace(char *env, char *value, t_parse *st)
{
	t_env	*tmp;

	tmp = st->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, env))
		{
			free (tmp->value);
			tmp->value = value;
			return ;
		}
		tmp = tmp->next;
	}
	add_key(env, value, st);
}

void	add_key(char *key, char *value, t_parse *st) //pass the head  of the list
{
	t_env	*new_key;

	new_key = malloc (sizeof(t_env *));
	if (!new_key)
		return ;// more protection nega
	new_key->key = ft_copy(key);
	new_key->value = ft_copy(value);
	if (!new_key->key || !new_key->value)
		return ;
	last_var(st->env)->next = new_key;
}
