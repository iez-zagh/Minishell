/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:19:56 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/07 18:49:51 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free (env);
		env = tmp;
	}
}

void	freeing(t_params *params)
{
	if (params->path)
		free(params->path);
	if (params->env)
		free_list(params->env);
	if (params->paths_array)
		ft_free(params->paths_array);
	if (params->env2)
		ft_free(params->env2);
	ft_malloc(0, 3);
}

void	ft_free(char **s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		free (s[i++]);
	free (s);
}

void	change_pwd_value(t_params *params)
{
	char	*tmp;

	tmp = get_key("PWD", params->env);
	if (tmp)
	{
		search_and_replace(ft_copy("OLDPWD"), ft_copy(tmp),
			&(params->env), 0);
		search_and_replace(ft_copy("OLDPWD"), ft_copy(tmp),
			&(params->sorted_env), 0);
	}
	else
	{
		search_and_replace(ft_copy("OLDPWD"), "",
			&(params->env), 0);
		search_and_replace(ft_copy("OLDPWD"), "",
			&(params->sorted_env), 0);
	}
	search_and_replace(ft_copy("PWD"), get_pwd(params),
		&(params->sorted_env), 0);
	search_and_replace(ft_copy("PWD"), get_pwd(params), &(params->env), 0);
}
