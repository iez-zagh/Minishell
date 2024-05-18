/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:22:17 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/05/18 11:13:41 by iez-zagh         ###   ########.fr       */
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
