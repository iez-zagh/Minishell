/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:00:20 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/07 00:27:22 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	first_cmd(int fds[2])
{
	close(fds[0]);
	if (dup2(fds[1], STDOUT_FILENO) == -1)
		return (1);
	close(fds[1]);
	return (0);
}

void	dup_in(t_params *params)
{
	if (first_cmd(params->fds))
	{
		close(params->fds[0]);
		close(params->fds[1]);
		exit (1);
	}
}

void	middle_cmd(t_params *params)
{
	close(params->fds[0]);
	if (dup2(params->fds[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit (1);
	}
	close(params->fds[1]);
}

int	last_cmd(int fds[2])
{
	close(fds[1]);
	if (dup2(fds[0], STDIN_FILENO) == -1)
		return (1);
	close(fds[0]);
	return (0);
}

void	forking_piping(t_params *params)
{
	if (params->flag && params->i > 1 && params->flag_2)
	{
		close (params->save_fd);
		params->save_fd = params->fds[0];
	}
	if (params->i == 0 && params->cmds > 1)
		dup_in(params);
	else
	{
		if (params->i)
		{
			if (dup2(params->save_fd, STDIN_FILENO) == -1)
			{
				perror("dup2");
				exit (1);
			}
			close(params->fds[0]);
		}
		if (params->i != params->cmds - 1 && params->i)
			middle_cmd(params);
	}
}
