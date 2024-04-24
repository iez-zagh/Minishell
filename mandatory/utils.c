/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 20:52:27 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/04/24 01:54:05 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	excute_cmd(t_parse *st)
{
	int	pid;

	if (ft_strncmp(st->com_arr[0], "cd", 2) == 0)
	{
		change_directory(st);
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
	if (stat(st->com_arr[1], &the_path) == -1)
	{
		perror("stat");
		return;
	}
	if (!S_ISDIR(the_path.st_mode)) {
		printf("cd: not a directory: %s\n", st->com_arr[1]);
		return;
	}
	if (chdir(st->com_arr[1]) == -1)
		printf("cd: no such file or directory: %s\n", st->com_arr[1]);
}
