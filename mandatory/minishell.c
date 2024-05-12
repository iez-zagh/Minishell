/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:50:33 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/05/12 23:42:11 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void leaks(void)
{
	system("leaks minishell");
}

int main(int __attribute__((unused)) argc, char __attribute__((unused)) * argv[], char *env[])
{
	t_parse *st;	

	// atexit(leaks);
	st = malloc(sizeof(t_parse));
	if (!st)
		error(st, 2);
	st->path = getenv("PATH");
	if (!env[0])
		empty_env(env, st);
	st->paths_array = ft_split(st->path, ':');
	st->env = NULL;
	set_env(&st->env, env);
	list2array(st->env, st);
	wait_prompt(st);
}

void error(t_parse *st, int y)
{
	if (y == 1)
		printf("an error accored in the forking proccess !\n");
	else if (y == 2)
		printf("allocation failure\n");
	else if (y == 3)
		ft_free(st->paths_array);
	else if (y == 4)
		printf("%s :command not found\n", st->arr);
	else if (y == 5)
		printf("exit\nShellantics: exit: %s: numeric argument required\n", st->com_arr[1]);
	else if (y == 6)
		printf("error while geting working path\n");
	exit(1);
}

void signal_handler(int signum, t_parse *st)
{
	if (signum == SIGINT)
	{
		printf("\n");
		wait_prompt(st);
	}
	else if (signum == SIGQUIT)
	{
		free(st->paths_array);
		exit(0);
	}
}

void wait_prompt(t_parse *st)
{
	while (1)
	{
		signal(SIGTERM, (void *)signal_handler);
		st->arr = readline("Shellantics-1.0$ ");
		if (!st->arr)
			error(st, 3);
		add_history(st->arr);
		if (checking_cmd(st))
			continue ;
		 puts("hi");
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
