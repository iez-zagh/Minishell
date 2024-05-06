/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 20:52:27 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/05/06 11:27:13 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	excute_cmd(t_parse *st)
{
	int	pid;

	if (ft_strncmp(st->com_arr[0], "cd", 2) == 0)
	{
		change_directory(st);
		return 
			;
	}
	if (ft_strncmp(st->com_arr[0], "..", 2) == 0 || ft_strncmp(st->com_arr[0], ".", 1) == 0)
	{
		return ;
	}
	pid = fork();
	if (pid == 0)
		execve(st->com_path, st->com_arr, st->env2);
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
	stat(st->com_arr[1], &the_path);
	if (!S_ISDIR(the_path.st_mode))
	{
		printf("cd: not a directory: %s\n", st->com_arr[1]);
		return;
	}
	if (chdir(st->com_arr[1]) == -1)
		printf("cd: no such file or directory: %s\n", st->com_arr[1]);
}

void	excute_file(t_parse *st)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		execve(st->com_arr[0], st->com_arr, st->env2);
	wait (0);
}

void	terminate_shell(t_parse *st)
{
	int	args_n;

	args_n = count_args(st->com_arr);
	if ((numbered_args(&st->com_arr[1])))
		printf("exit\nShellantics: exit: numeric argument required\n");
	else if (args_n > 2 && (numbered_args(&st->com_arr[1])))
	{
		printf("exit\nShellantics: exit: too many arguments\n");
		return ;
	}
	printf("exit\n");
	free (st);
	exit (0);
}

int	count_args(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

