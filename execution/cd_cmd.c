/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:22:17 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/07/18 15:50:24 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_pwd_value(t_params *params)
{
	search_and_replace("OLDPWD", ft_copy(get_key("PWD", params->env)), &(params->env), 1);
	search_and_replace("PWD", get_pwd(params), &(params->env), 1);
}

t_env	*before_last_node(t_env *env)
{
	while (env->next->next)
		env = env->next;
	return (env);
}

void	ft_swap(t_env *a, t_env *b)
{
	char	*temp_key;
	char	*temp_value;

	temp_key = a->key;
	temp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
}

void	sort_env(t_env *env)
{
	t_env	*tmp;
	int		sorted;

	if (env == NULL)
		return ;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		tmp = env;
		while (tmp->next)
		{
			if (ft_strcmp(tmp->key, tmp->next->key) > 0)
			{
				ft_swap(tmp, tmp->next);
				sorted = 0;
			}
			tmp = tmp->next;
		}
	}
}

void	just_export(t_params *params)
{
	t_env	*tmp;

	tmp = params->sorted_env;
	while (tmp)
	{
		if (!(ft_strcmp("_", tmp->key)))
		{
			tmp = tmp->next;
			continue ;
		}
		if (!tmp->value)
			printf("declare -x %s\n", tmp->key);
		else
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void	export_cmd1(t_parse *st, t_params *params)
{
	int		i;
	char	**res;

	if (count_args(st->cmd) == 1) //handle the "export" yooo i am here
	{
		just_export(params);
		return ;
	}
	i = 1;
	while (st->cmd[i])
	{
		if (check_syntax(st->cmd[i]))
			printf("Shellantics: export: `%s': not a valid identifier\n", st->cmd[i]);
		else
		{
			check_join(&(st->cmd[i]), st, params);
			res = export_checker(st->cmd[i]);
			if (!res)
				error(st, 7, params);
			export_cmd(res, st->cmd[i], params);
		}
		i++;
	}
}
