/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 20:52:27 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/07/23 16:03:24 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	excute_cmd(t_parse *st, t_params *params)
{
	if (params->pid == 0)
		execve(st->com_path, st->cmd, params->env2);
}

void change_directory(t_parse *st, t_params *params)
{
	char	*home;

	if (count_args(st->cmd) == 1)
	{
		home = get_key("HOME", params->env);
		if (!home)
		{
			printf("Shellantics: cd: HOME not set\n");
			return ;
		}
		change_dir(st, params, home);
		return ;
	}
	change_dir(st, params, st->cmd[1]);
}

void	terminate_shell(t_parse *st, t_params *params)
{
	int	args_n;

	args_n = count_args(st->cmd);
	if (args_n == 1 || args_n == 2)
		ft_exit(st, args_n, params);
	if (!(numbered_arg(st->cmd[1])) && (count_args(st->cmd)) > 2)
	{
		printf("exit\nShellantics: exit: too many arguments\n");
		return ;//its one 
	}
	if ((numbered_arg(st->cmd[1])))
	{
		printf("exit\nShellantics: exit: %s: numeric argument required\n", st->cmd[1]);
		// freeing(st, params);
		exit (255);
	}
}
