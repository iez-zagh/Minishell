/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:50:33 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/05/17 17:51:45 by iez-zagh         ###   ########.fr       */
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

	atexit(leaks);
	st = malloc(sizeof(t_parse));
	if (!st)
		error(st, 2);
	if (!env[0])
		empty_env(env, st);
	st->env = NULL;
	set_env(&st->env, env);
	list2array(st->env, st);
	st->path = ft_copy(get_key("PATH", st->env)); //handle empty path or else
	st->paths_array = ft_split(st->path, ':');
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
		puts("hello there\n");
		printf("\n");
		wait_prompt(st);
	}
	else if (signum == SIGQUIT)
	{
		freeing(st);
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
		st->com_path = get_acc_path(st->paths_array, st->com_arr[0]);
		if (!st->com_path)
			printf("%s :command not found\n", st->com_arr[0]);
		else
			excute_cmd(st);
		freeing2(st);
	}	
}
