/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expanding.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:00:35 by houamrha          #+#    #+#             */
/*   Updated: 2024/08/06 16:15:24 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	set_value(char **line, t_params *params, t_decl2 *decl)
{
	if ((*line)[decl->start] == '?')
	{
		if (g_status == 2)
			decl->value = ft_strdup(ft_itoa(1));
		else
			decl->value = ft_strdup(ft_itoa(params->status));
	}
	else
		decl->value = get_key(fmysubstr(*line,
					decl->start, decl->i - decl->start), params->env);
	if (decl->value)
		decl->n_t_v = ft_strjoin(decl->n_t_v, decl->value);
	else
		decl->n_t_v = ft_strjoin(decl->n_t_v, "");
}

void	expand_line(char **line, t_params *params)
{
	t_decl2	decl;

	42 && (decl.n_t_v = NULL, decl.i = 0);
	while ((*line)[decl.i])
	{
		decl.start = decl.i;
		while ((*line)[decl.i] && (*line)[decl.i] != '$')
			decl.i++;
		decl.n_t_v = ft_strjoin(decl.n_t_v,
				fmysubstr(*line, decl.start, decl.i - decl.start));
		if ((*line)[decl.i])
			decl.i++;
		decl.start = decl.i;
		if ((*line)[decl.i]
				&& !is_alph((*line)[decl.i]) && (*line)[decl.i] != '_')
			decl.i++;
		else
		{
			while ((*line)[decl.i]
				&& (is_alph_num((*line)[decl.i]) || (*line)[decl.i] == '_'))
				decl.i++;
		}
		set_value(line, params, &decl);
	}
	*line = decl.n_t_v;
}
