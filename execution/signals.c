/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:28:03 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/07 12:52:55 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_handler(int sig)
{
	if (!(waitpid(-1, NULL, WNOHANG)))
		return ;
	if (sig == SIGINT)
	{
		g_status = SIGINT;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_handle(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

int	minishell(t_parse *st)
{
	char	*tmp;

	tmp = ft_substr(st->cmd[0], 2, ft_strlen(st->cmd[0]));
	if (!access(tmp, X_OK))
	{
		st->com_path = ft_copy(st->cmd[0]);
		free (tmp);
		return (1);
	}
	free (tmp);
	return (0);
}

void	malloc_error(t_params *params)
{
	perror("malloc");
	freeing(params);
	ft_malloc(3, 0);
	exit (1);
}
