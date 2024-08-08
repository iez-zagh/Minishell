/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:02:07 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/07 18:07:41 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exiting(t_params *params, int status)
{
	close(params->fds[0]);
	close(params->fds[1]);
	exit (status);
}

void	signal_fds(t_params *params)
{
	int	status;

	status = 0;
	waitpid(params->pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2
			|| WTERMSIG(status) == 3)
		{
			status = WTERMSIG(status) + 128;
			if (WTERMSIG(status) == 3)
				write(1, "Quit: 3\n", 8);
			if (WTERMSIG(status) == 2)
				write(1, "\n", 1);
			params->status = status;
		}
	}
	if (WIFEXITED(status))
		params->status = WEXITSTATUS(status);
	close(params->fds[0]);
	close(params->fds[1]);
}

void	closing_fds(t_params *params)
{
	close (params->fds[1]);
	if (params->save_fd != -1)
		close (params->save_fd);
	if (params->i == params->cmds - 1)
		signal_fds(params);
	params->flag = 0;
	if (params->i != params->cmds - 1)
	{
		params->save_fd = params->fds[0];
		params->flag_2 = 1;
	}
	else
		close (params->fds[0]);
}

void	executing(t_parse *st, t_params *params)
{
	int	status;

	status = 0;
	params->flag = 0;
	pipe(params->fds);
	params->pid = fork();
	if (fork_failure(params))
		return ;
	if (!params->pid)
	{
		forking_piping(params);
		if (just_a_checker(st, params))
			exit (1);
		if (check_builtins(st->cmd[0]))
			status = checking_cmd(st, params);
		else
		{
			slash_path(st, params);
			checking_and_exec(st, params);
		}
		exiting(params, status);
	}
	closing_fds(params);
}

void	excute_cmds(t_parse *st, t_params *params)
{
	if (params->cmds == 1 && check_builtins(st->cmd[0]))
	{
		if (just_a_checker(st, params))
			params->status = 1;
		else
			params->status = checking_cmd(st, params);
		if (params->stdout_ != -1)
		{
			dup2(params->stdout_, STDOUT_FILENO);
			close (params->stdout_);
		}
		if (params->stdin_ != -1)
		{
			dup2(params->stdin_, STDIN_FILENO);
			close (params->stdin_);
		}
	}
	else
		executing(st, params);
}
