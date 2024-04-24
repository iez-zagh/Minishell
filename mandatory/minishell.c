/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:50:33 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/04/24 01:09:35 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char __attribute__((unused))*argv[], char *env[])
{
	t_parse	*st;

	atexit(leaks);
	if (argc != 1 || !*env)
		return (1);
	st = malloc(sizeof(t_parse));
	if (!st)
		error(st, 2);
	st->env2 = env;
	st->env = getenv("PATH");
	st->paths_array = ft_split(st->env, ':');
	wait_prompt(st);
}

void	error(t_parse *st, int y)
{
	if (y == 1)
		printf("an error accored in the forking proccess !\n");
	else if (y == 2)
		printf("allocation failure\n");
	else if (y == 3)
		printf("exit\n");
	else if (y == 4)
		printf("%s :command not found\n", st->arr);
	if (st)
		free(st);
	exit(1);
}

void	signal_handler(int signum, t_parse *st)
{
	if (signum == SIGUSR1)
		exit(1);
	if (signum == SIGINT)
	{
		printf("\n");
		wait_prompt(st);
	}
	else if (signum == SIGQUIT)
		exit(0);
	// else if (signum == SIGTSTP)
	// {
	// 	printf("\nReceived SIGTSTP (Ctrl+Z)\n");
	// }
	// else if (signum == SIGTERM)
	// {
	// 	printf("\nReceived SIGTERM\n");
	// }
}

void	wait_prompt(t_parse *st)
{
	while (1)
	{
		// signal(SIGINT, (void *)signal_handler);
		st->arr = readline(BLUE_TEXT"Shellantics ~:"RESET_TEXT);
		if (!st->arr)
			error(st, 3);
		if (ft_strlen(st->arr) == 0)
			continue ;
		add_history(st->arr);
		st->com_arr = ft_split(st->arr, ' ');
		st->com_path = get_acc_path(st->paths_array, st->com_arr[0]);
		if (!st->com_path)
			printf("%s :command not found\n", st->arr);
		else
			excute_cmd(st);
		ft_free(st->com_arr);
		free(st->arr);
		free(st->com_path);
	}
}
