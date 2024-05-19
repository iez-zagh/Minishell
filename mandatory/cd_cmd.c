/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:22:17 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/05/19 20:17:43 by iez-zagh         ###   ########.fr       */
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

	if (env == NULL)
		return;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		while (env)
		{
			if (ft_strcmp(env->key, env->key) > 0)
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
	ft_swap2(&(*a)->key, &(*b)->key);
	ft_swap2(&(*a)->value, &(*b)->value);
}

void	just_export(t_parse *st) //handle the linked list
{
	while (st->sorted_env)
	{
		printf("%s=%s\n", st->sorted_env->key, st->sorted_env->value); //remember to free  this shit on exit
		st->sorted_env = st->sorted_env->next;
	}
}

void	copy_env(t_parse *st)
{
	t_env	*new;

	st->sorted_env = NULL;
	while (st->env)
	{
		new = malloc (sizeof(t_env));
		if (new)
			return ;// handle the malloc failure
		new->key = ft_copy(st->env->key);
		new->value = ft_copy(st->env->value);
		add_var(&st->sorted_env, new);
		st->env = st->env->next;
	}
}

// void	add_node(t_env **env, t_env *new)
// {
// 	if (count_list(*env) == 1)
// 		return ;
// 	(*env)->next = new;
// 	new->next = NULL;
// }

// int	count_list(t_env *env) //maybe i'll need it some time
// {
// 	int	counter;

// 	counter = 0;
// 	while (env)
// 	{
// 		counter++;
// 		env = env->next;
// 	}
// 	return (counter);
// }