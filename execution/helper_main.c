/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:01:37 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/07 18:15:33 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	no_path(t_parse *st, t_params *params)
{
	if (!params->pid)
	{
		close (params->fds[0]);
		close (params->fds[1]);
	}
	params->flag = 1;
	print_error(st->cmd[0], ": No such file or directory\n", NULL);
	exit (127);
}

int	just_a_checker(t_parse *st, t_params *params)
{
	if (st->files || st->in_dup)
	{
		if (in_out_dup(st, params))
			return (1);
	}
	if (!st || !st->cmd[0] || (!st->files && !st->cmd))
		return (1);
	return (0);
}

void	checking_and_exec(t_parse *st, t_params *params)
{
	if (!st->com_path && st->cmd[0] && (!(get_key("PATH", params->env))
			&& ft_strcmp(st->cmd[0], "./minishell")))
		no_path(st, params);
	else if (!st->com_path || !ft_strlen(st->cmd[0]))
	{
		if (!params->pid)
		{
			close (params->fds[0]);
			close (params->fds[1]);
		}
		params->flag = 1;
		params->status = 127;
		print_error(st->cmd[0], ": command not found\n", NULL);
		exit (127);
	}
	excute_cmd(st, params);
}
