/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:22:17 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/05/20 17:07:31 by iez-zagh         ###   ########.fr       */
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

void	sort_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strcmp(env[i], env[i + 1]) > 0)
		{
			ft_swap2(&env[i], &env[i + 1]);
			i = -1;
		}
		i++;
	}
}

// void sort_env(t_env *env)
// {
// 	t_env	*tmp;
// 	t_env	**head;
// 	int		sorted;

// 	if (env == NULL)
// 		return;
// 	sorted = 0;
// 	tmp = env;
// 	head = &env;
// 	while (!sorted)
// 	{
// 		sorted = 1;
// 		tmp = *head;
// 		while (tmp->next)
// 		{
// 			if (ft_strcmp(tmp->key, tmp->next->key) > 0)
// 			{
// 				ft_swap(&tmp, &tmp->next);
// 				sorted = 0;
// 			}
// 			tmp = tmp->next;
// 		}
// 	}
// }

void	ft_swap2(char **a, char **b)
{
	char	*c;

	c = *a;
	*a = *b;
	*b = c;
}
 
void	ft_swap(t_env **a, t_env **b)
{
  t_env *temp = *a;
    *a = (*a)->next;
    temp->next = (*a)->next;
    (*a)->next = temp;
    *b = *a;
	// ft_swap2(&(*a)->key, &(*b)->key);
	// ft_swap2(&(*a)->value, &(*b)->value);
}

void	just_export(t_parse *st) //handle the linked list
{
	while (st->sorted_env)
	{
		printf("%s=%s\n", st->sorted_env->key, st->sorted_env->value); //remember to free  this shit on exit
		st->sorted_env = st->sorted_env->next;
	}
}
