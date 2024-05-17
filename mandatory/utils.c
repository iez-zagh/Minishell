/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 20:52:27 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/05/16 16:23:32 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	excute_cmd(t_parse *st)
{
	int	pid;

	list2array(st->env, st);
	pid = fork();
	if (pid == 0)
		execve(st->com_path, st->com_arr, st->env2); //protection
	wait(0);
	return ;
}

void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free (s[i++]);
	free (s);
}

void change_directory(t_parse *st)
{
	struct stat the_path;
	char		*home;

	if (count_args(st->com_arr) == 1)
	{
		home = get_key("HOME", st->env);
		st->com_arr[1] = home;
	}
	stat(st->com_arr[1], &the_path);
	if (!S_ISDIR(the_path.st_mode))
	{
		if (access(st->com_arr[1], F_OK) != -1)
		{
			printf("cd: not a directory: %s\n", st->com_arr[1]);
			return ;
		}
	}
	if (chdir(st->com_arr[1]) == -1)
	{
		printf("cd: no such file or directory: %s\n", st->com_arr[1]);	
		return ;
	}
	else
		change_pwd_value(st);
}

void	excute_file(t_parse *st)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		if (execve(st->com_arr[0], st->com_arr, st->env2) == -1)
			printf("Shellantics: %s: No such file or directory\n", st->com_arr[0]);
	wait (0);
}

void	terminate_shell(t_parse *st)
{
	int	args_n;

	args_n = count_args(st->com_arr);
	if (args_n == 1 || args_n == 2)
		ft_exit(st, args_n);
	if (!(numbered_arg(st->com_arr[1])) && (count_args(st->com_arr)) > 2)
	{
		printf("exit\nShellantics: exit: too many arguments\n");
		return ;
	}
	if ((numbered_arg(st->com_arr[1])))
	{
		printf("exit\nShellantics: exit: %s: numeric argument required\n", st->com_arr[1]);
		freeing(st);
		exit (255);
	}
}
