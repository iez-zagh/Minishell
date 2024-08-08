/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:01:22 by houamrha          #+#    #+#             */
/*   Updated: 2024/08/07 10:47:55 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_input(t_token **tokens, t_parse **new_parse)
{
	if (ft_strcmp((*tokens)->next->type, "WHITE") == 0)
		*tokens = (*tokens)->next;
	add_back_file(&(*new_parse)->files, 1, *tokens, *new_parse);
	(*tokens) = (*tokens)->next;
}

void	parse_output(t_token **tokens, t_parse **new_parse)
{
	if (ft_strcmp((*tokens)->next->type, "WHITE") == 0)
		(*tokens) = (*tokens)->next;
	add_back_file(&(*new_parse)->files, 2, *tokens, *new_parse);
	(*tokens) = (*tokens)->next;
}

void	parse_append(t_token **tokens, t_parse **new_parse)
{
	if (ft_strcmp((*tokens)->next->type, "WHITE") == 0)
		(*tokens) = (*tokens)->next;
	add_back_file(&(*new_parse)->files, 3, *tokens, *new_parse);
	(*tokens) = (*tokens)->next;
}

void	write_in_doc(t_decl3 *decl)
{
	write(decl->fd, decl->line, ft_strlen(decl->line));
	write(decl->fd, "\n", 1);
}

int	doc(t_decl3 *decl, t_token **tokens, t_parse **new_parse, t_params *params)
{
	(*new_parse)->i ++;
	if (ft_strcmp((*tokens)->next->type, "WHITE") == 0)
		(*tokens) = (*tokens)->next;
	(*new_parse)->in_dup = ft_strjoin("/tmp/h", ft_itoa((*new_parse)->i));
	decl->fd = open(ft_strjoin("/tmp/h", ft_itoa((*new_parse)->i)),
			O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (decl->fd == -1)
		return (perror("Opening Error!"), 0);
	while (1)
	{
		decl->line = readline("> ");
		if (!ttyname(0))
			return (signal_pro(decl, params), 0);
		if (!decl->line)
		{
			params->status = 0;
			break ;
		}
		if (ft_strcmp((*tokens)->next->value, decl->line) == 0)
			break ;
		if (!(*tokens)->next->has_q && in_str(decl->line, '$'))
			expand_line(&decl->line, params);
		write_in_doc(decl);
	}
	return (close(decl->fd), (*tokens) = (*tokens)->next, 1);
}
