/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander1_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:58:22 by houamrha          #+#    #+#             */
/*   Updated: 2024/08/06 16:25:53 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*set_status(int status)
{
	if (g_status == 2)
		return (ft_strdup(ft_itoa(1)));
	else
		return (ft_strdup(ft_itoa(status)));
}

void	comp(t_decl decl, t_token **token, char *token_value, int *i)
{
	if (decl.still)
		add_middle_n(token, fmysubstr(token_value,
				decl.first, *i - decl.first));
	else
		(*token)->value = ft_strjoin((*token)->value,
				fmysubstr(token_value, decl.first, *i - decl.first));
}

void	first_word_pos(char *value, int *i, int *j)
{
	int	k;

	k = 0;
	while (value[k] && is_white(value[k]))
		k ++;
	*i = k;
	while (value[k] && !is_white(value[k]))
		k ++;
	*j = k;
}

void	not_w_first_i(t_decl *decl, char **n_t_v, t_token **token)
{
	while (decl->value[decl->j] && !is_white(decl->value[decl->j]))
		decl->j++;
	if (!(*token)->flag && !decl->still)
		*n_t_v = ft_strjoin(*n_t_v, fmysubstr(decl->value, 0, decl->j));
	else
	{
		if (decl->still)
			add_middle_n(token, fmysubstr(decl->value, 0, decl->j));
		else
			(*token)->value = ft_strjoin((*token)->value,
					fmysubstr(decl->value, 0, decl->j));
	}
	if (decl->value[decl->j] && no_rest(decl->value, decl->j))
		decl->still = 1;
	else
		decl->still = 0;
}
