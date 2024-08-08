/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 20:52:27 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/07 14:45:27 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	excute_cmd(t_parse *st, t_params *params)
{
	if (!params->pid)
		execve(st->com_path, st->cmd, params->env2);
}

int	change_directory(t_parse *st, t_params *params)
{
	char	*home;

	if (count_args(st->cmd) == 1)
	{
		home = get_key("HOME", params->env);
		if (!home)
			return (print_error("cd", ": HOME not set\n", NULL), 1);
		return (change_dir(st, params, home));
	}
	if (!ft_strcmp(st->cmd[1], "."))
		return (print_error("cd",
				": no such file or directory\n", "."), 1);
	return (change_dir(st, params, st->cmd[1]));
}

int	terminate_shell(t_parse *st, t_params *params)
{
	int	args_n;

	args_n = count_args(st->cmd);
	if (args_n == 1 || args_n == 2)
		ft_exit(st, args_n, params);
	if (!(numbered_arg(st->cmd[1])) && (count_args(st->cmd)) > 2)
	{
		write(2, "exit\n", 5);
		print_error("exit", ": too many arguments\n", NULL);
		return (1);
	}
	if ((numbered_arg(st->cmd[1])))
	{
		write(2, "exit\n", 5);
		print_error("exit", ": numeric argument required\n", NULL);
		freeing(params);
		exit (255);
	}
	return (0);
}

void	forking_checker(t_parse *st, t_params *params)
{
	slash_path(st, params);
	if (params->cmds > 1 && isatty(1))
		forking_piping(params);
}

void	initialiaze_vars(t_params *params, t_token **token, int f)
{
	if (f)
	{
		params->flag = 0;
		*token = NULL;
	}
	params->pid = 1;
	params->flag_2 = 0;
	params->save_fd = -1;
	params->i = 0;
	rl_catch_signals = 0;
}
