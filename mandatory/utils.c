/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 20:52:27 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/05/08 16:03:07 by iez-zagh         ###   ########.fr       */
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
	if (!ft_strcmp(st->com_arr[0], ".."))
	{
		printf("%s: command not found\n",st->com_arr[0]);
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

int	count_args(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	freeing(t_parse *st)
{
	ft_free(st->com_arr);
	ft_free(st->paths_array);
	free(st->arr);
	free (st);
}

void	free_list(t_env *env)
{
	t_env	*tmp;
	
	while (env)
	{
		tmp = env->next;
		free (env);
		env = tmp;
	}
}