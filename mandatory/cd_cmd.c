/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:22:17 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/05/19 16:36:03 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	void	change_pwd_value(t_parse *st)
	{
		search_and_replace("OLDPWD", ft_copy(get_key("PWD", st->env)), &st, 1);
		search_and_replace("PWD", get_pwd(st), &st, 1);
	}

	t_env	*before_last_node(t_env *env)
	{
		while (env->next->next)
		env = env->next;
	return (env);
}

// void	sort_env(char **env)
// {
// 	char	**tmp;
// 	int		i;

// 	i = 0;
// 	tmp = env;
// 	while (tmp[i])
// 	{
// 		if (ft_strcmp(tmp[i], tmp[i + 1]) > 0)
// 		{
// 			ft_swap(&tmp[i], &tmp[i + 1]);
// 			tmp = env;
// 		}
// 		i++;
// 	}
// }

void sort_env(t_env *env)
{
	int	sorted;
	int	i;

	if (env == NULL)
		return;
	sorted = 0;
	i = 0;
	while (!sorted)
	{
		sorted = 1;
		while (env->key[i + 1])
		{
			if (ft_strcmp(env->key[i], env->key[i + 1]) > 0)
			{
				ft_swap(&env, &env);
				sorted = 0;
			}
		}
	}
}

void	ft_swap2(char **a, char **b)
{
	char	*c;

	c = *a;
	*a = *b;
	*b = c;
}

void	ft_swap(t_env **a, t_env **b)
{
	ft_swap((*a)->key, (*b)->key);
	ft_swap((*a)->value, (*b)->value);
}

void	just_export(t_parse *st)
{
	int i = 0;

	while (st->sorted_env[i])
	{
		printf("%s\n", st->sorted_env[i]); //remember to free  this shit on exit
		i++;
	}
}
