/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:01:07 by houamrha          #+#    #+#             */
/*   Updated: 2024/08/06 15:05:51 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_pro(t_decl3 *decl, t_params *params)
{
	open(ttyname(2), O_RDWR, 0777);
	close(decl->fd);
	params->status = 1;
}

t_files	*last_node_files(t_files *files)
{
	while (files->next)
		files = files->next;
	return (files);
}

void	add_back_file(t_files **files, int type, t_token *token, t_parse *parse)
{
	t_files	*new;

	new = ft_malloc(sizeof(t_files), 1);
	new->file = ft_strdup(token->next->value);
	if (token->next->flag)
		new->is_amb = 1;
	else
		new->is_amb = 0;
	new->type = type;
	if (type == 1)
		parse->in_dup = new->file;
	else
		parse->out_dup = new->file;
	new->next = NULL;
	if (!*files)
		*files = new;
	else
		last_node_files(*files)->next = new;
}
