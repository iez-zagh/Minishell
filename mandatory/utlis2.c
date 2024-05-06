/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:05:38 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/05/06 11:08:55 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2
			&& *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	checking_cmd(t_parse *st)
{
	if (ft_strlen(st->arr) == 0)
		return (1);
	st->com_arr = ft_split(st->arr, ' ');
	if (!(ft_strcmp(st->com_arr[0], "exit")))
	{
		terminate_shell(st);
		return (1);
	}
	if (st->arr[0] == '.' && st->arr[1] == '/')
	{
		excute_file(st);
		returnn (1);
	}
	if (!strcmp("env", st->com_arr[0]))
	{
		if (env_cmd(st))
			retur (1);
	}
	return (0);
}

int	env_cmd(t_parse	*st)
{
	if (numbered_arg()
}