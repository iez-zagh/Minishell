/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:00:24 by houamrha          #+#    #+#             */
/*   Updated: 2024/08/06 16:19:49 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	garbage_collector(t_garbage **gr, void	*p)
{
	t_garbage	*tmp;
	t_garbage	*new_g;

	new_g = malloc(sizeof(t_garbage));
	if (!new_g)
	{
		ft_malloc(0, 3);
		perror("Malloc error!");
		exit(1);
	}
	new_g->next = NULL;
	new_g->p = p;
	if (!*gr)
		*gr = new_g;
	else
	{
		tmp = *gr;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_g;
	}
}

void	empty_garbage(t_garbage **gr)
{
	t_garbage	*tmp;

	while (*gr)
	{
		tmp = *gr;
		*gr = (*gr)->next;
		free(tmp->p);
		free(tmp);
	}
}

void	*ft_malloc(size_t size, int flag)
{
	void				*p;
	static t_garbage	*gr;

	if (flag == 1 || flag == 0)
	{
		p = malloc(size);
		if (!p)
		{
			perror("Malloc error!");
			ft_malloc(0, 3);
			exit(1);
		}
		else
			if (flag)
				garbage_collector(&gr, p);
		return (p);
	}
	else
		empty_garbage(&gr);
	return (NULL);
}
