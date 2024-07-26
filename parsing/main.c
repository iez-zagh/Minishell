#include "../minishell.h"

void	parser_reset(t_parse **st)
{
	while (*st)
	{
		if ((*st)->in_fd)
			close((*st)->in_fd);
		(*st) = (*st)->next;
	}
}

void	slash_path(t_parse *st, t_params *params)
{
	if (!st->cmd || !st->cmd[0]
		|| !(ft_strcmp(".", st->cmd[0])) || !(ft_strcmp("..", st->cmd[0])))
		st->com_path = NULL;
	else if (access(st->cmd[0], X_OK))
		st->com_path = get_acc_path(params->paths_array, st->cmd[0]);
	else
		st->com_path = ft_copy(st->cmd[0]);
}

int	just_a_checker(t_parse *st, t_params *params)
{
	// print(st);
	if (st->files || st->in_fd || st->in_dup) //add redidrection to the pipes
	{
		if (in_out_dup(st, params))
			return (1);
	}
	if (!st || !st->cmd[0] || (!st->files && !st->cmd))
		return (1);
	return (0);
}

void	wait_prompt1(t_params *params)
{
	t_token		*token;
	t_parse		*st;
	int			i;

	initialiaze_vars(params, &i, &token, 1);
	st = NULL;
	token = NULL;
	while (1)
	{
		signal_handle();
		params->q = 0;
		params->line = readline("• Shellantics$ ");
		if (!params->line)
			break ; // exit with 1
		add_history(params->line);
		tokenize(&token, params->line, &params->q);
		if (!params->q)
		{
			if (!syntax(token))
			{
				expander(token, *params);
				parser(token, &st, params);
				params->cmds = lstsize(st);
				// print(st);
				while (st)
				{
					update_(st, params);
					forking_checker(st, params, i);
					if ((!(params->pid) || (params->cmds == 1 && params->pid )) && just_a_checker(st, params))
					{
						tokens_reset(&token);
						parser_reset(&st);
						if (!params->pid)
							exit (0);
						continue ;
					}
					if ((!(params->pid) || (params->cmds == 1 && params->pid )) && checking_cmd(st, params))
					{
						tokens_reset(&token);
						parser_reset(&st);
						if (!params->pid)
							exit (0);
						continue ;
					}
					if (!params->path && params->pid)
					{
						while (st->next)
							st = st->next;
						printf("Shellantics: %s: No such file or directory\n", st->cmd[0]);
						tokens_reset(&token);
						parser_reset(&st);
						if (!params->pid)
							exit (0);
						continue ;
					}
					if (((!(params->pid)) || (params->cmds == 1 && params->pid )) && checking_cmd2(st, params))
					{
						tokens_reset(&token);
						parser_reset(&st);
						if (!params->pid)
							exit (0);
						continue ;
					}
					if (!st->com_path || !ft_strlen(st->cmd[0])) //check the "." and ".."
					{
						if (!params->pid)
						{
							close (params->fds[0]);
							close (params->fds[1]);
							exit (0);
						}
						params->flag = 1;
						params->status = 127;
						printf("shellantics: %s :command not found\n", st->cmd[0]); //this is just a function
					}
					else
						excute_cmd(st, params);
					if (params->pid != 0)
					{
						if (i == params->cmds - 1)
						{
							waitpid(params->pid, 0, 0);
							// close(fds[0]);
							// close(fds[1]);
						}
						params->flag = 0; // this could cause a problem
						if (i != 0)
							close(params->save_fd);
   						if (i != params->cmds - 1)
   						{
   					   		close(params->fds[1]);
							params->save_fd = params->fds[0];
							params->flag_2 = 1;
   						}
					}
					st = st->next;
					i++;
				}
				initialiaze_vars(params, &i, &token, 0);
				while (wait(0) != -1 || errno != ECHILD)
					;
			}
		}
		tokens_reset(&token);
		parser_reset(&st);
	}
}