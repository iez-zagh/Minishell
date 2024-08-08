/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:41:22 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/07 17:35:02 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	starting_excute(t_parse *st, t_params *params, t_token *token)
{
	if (!syntax(token, params))
	{
		expander(token, *params);
		if (!parser(token, &st, params))
			return ;
		params->cmds = lstsize(st);
		while (st)
		{
			update_(st, params);
			signal_handle();
			excute_cmds(st, params);
			st = st->next;
			params->i++;
		}
		while (waitpid(-1, NULL, 0) > 0 || errno != ECHILD)
			;
		initialiaze_vars(params, &token, 0);
	}
}

void	readline_failure(t_params *params)
{
	freeing(params);
	ft_malloc(0, 3);
	write (1, "exit\n", 5);
	exit (0);
}

void	wait_prompt1(t_params *params)
{
	t_token		*token;
	t_parse		*st;

	initialiaze_vars(params, &token, 1);
	params->status = 0;
	st = NULL;
	token = NULL;
	while (1)
	{
		signal_handle();
		params->q = 0;
		params->line = readline("• Shellantics$ ");
		if (!params->line)
			readline_failure(params);
		add_history(params->line);
		tokenize(&token, params->line, params);
		if (!params->q)
			starting_excute(st, params, token);
		token = NULL;
		st = NULL;
		ft_malloc(0, 3);
		if (params->line)
			free (params->line);
	}
}
