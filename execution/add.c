/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:01:24 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/07 18:15:07 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fork_failure(t_params *params)
{
	if (params->pid == -1)
	{
		params->status = 1;
		write(2, "fork: Resource temporarily unavailable", 38);
		return (1);
	}
	return (0);
}

int	open_fs(t_parse *st, int out)
{
	st->out_fd = -2;
	st->in_fd = -2;
	if (st->out_dup && out == 2)
		st->out_fd = open(st->out_dup, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (st->out_dup && out == 3)
		st->out_fd = open(st->out_dup, O_WRONLY | O_CREAT
				| O_APPEND, 0644);
	if (st->in_dup)
		st->in_fd = open(st->in_dup, O_RDONLY);
	if (st->out_fd == -1 || st->in_fd == -1)
		return (perror("open"), 1);
	return (0);
}
