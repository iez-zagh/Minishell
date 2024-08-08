/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:02:35 by houamrha          #+#    #+#             */
/*   Updated: 2024/07/30 11:02:43 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_new_value(t_decl2 *decl, t_token *tokens)
{
	if (!decl->in_quote)
	{
		while (tokens->value[decl->i] && tokens->value[decl->i] != '\''
			&& tokens->value[decl->i] != '"')
		{
			decl->value[decl->j] = tokens->value[decl->i];
			decl->j++;
			decl->i++;
		}
	}
	else
	{
		while (tokens->value[decl->i] && tokens->value[decl->i] != decl->quote)
		{
			decl->value[decl->j] = tokens->value[decl->i];
			decl->j++;
			decl->i++;
		}
	}
}

void	quotes_removal(t_token *tokens)
{
	t_decl2	decl;

	decl.in_quote = 0;
	decl.i = 0;
	decl.j = 0;
	if (ft_strcmp(tokens->type, "WORD") == 0
		&& (in_str(tokens->value, '\'') || in_str(tokens->value, '"')))
	{
		tokens->has_q = 1;
		decl.value = ft_malloc(ft_strlen(tokens->value) + 1, 1);
		if (!decl.value)
			return ;
		while (tokens->value[decl.i])
		{
			is_in_quote(&decl, tokens->value);
			set_new_value(&decl, tokens);
		}
		decl.value[decl.j] = '\0';
		tokens->value = decl.value;
	}
	else
		tokens->has_q = 0;
}
