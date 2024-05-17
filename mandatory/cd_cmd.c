/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:22:17 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/05/17 10:07:04 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_pwd_value(t_parse *st)
{
	search_and_replace("OLDPWD", ft_copy(get_key("PWD", st->env)), &st);
	search_and_replace("PWD", get_pwd(st), &st);
}

t_env	*before_last_node(t_env *env)
{
	while (env->next->next)
		env = env->next;
	return (env);
}
