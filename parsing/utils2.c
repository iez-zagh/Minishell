/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:03:50 by houamrha          #+#    #+#             */
/*   Updated: 2024/07/30 11:03:52 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*last_node(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_parse	*last_node_parse(t_parse *parse)
{
	t_parse	*tmp;

	tmp = parse;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	add_back(t_token **token, t_token *new)
{
	if (!*token)
		*token = new;
	else
		last_node(*token)->next = new;
}

void	add_back_parse(t_parse **parse, t_parse *new)
{
	if (!*parse)
		*parse = new;
	else
		last_node_parse(*parse)->next = new;
}

void	add_middle(t_token **token, char **arr)
{
	t_token	*tmp;
	t_token	*new;
	int		i;

	i = 0;
	while (arr[i])
	{
		new = ft_malloc(sizeof(t_token), 1);
		new->next = NULL;
		new->type = ft_strdup("WORD");
		new->value = ft_strdup(arr[i]);
		tmp = (*token)->next;
		(*token)->flag = 1;
		(*token)->next = new;
		new->next = tmp;
		*token = (*token)->next;
		i++;
	}
}
