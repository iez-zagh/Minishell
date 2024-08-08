/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:59:19 by houamrha          #+#    #+#             */
/*   Updated: 2024/08/06 16:27:06 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	not_w_first_i_2(t_decl2 *decl, t_token **token)
{
	while (decl->value[decl->z] && !is_white(decl->value[decl->z]))
		decl->z++;
	if (!(*token)->flag && !decl->still)
		decl->n_t_v = ft_strjoin(decl->n_t_v,
				fmysubstr(decl->value, 0, decl->z));
	else
	{
		if (decl->still)
			add_middle_n(token, fmysubstr(decl->value, 0, decl->z));
		else
			(*token)->value = ft_strjoin((*token)->value,
					fmysubstr(decl->value, 0, decl->z));
	}
	decl->still = 0;
	if (decl->value[decl->z] && no_rest(decl->value, decl->z))
		decl->still = 1;
}

void	out_quotes_not_key(t_decl2 *decl, char *t_v, t_token **token)
{
	decl->start = decl->i;
	while (t_v[decl->i] && t_v[decl->i] != '\''
		&& t_v[decl->i] != '"' && t_v[decl->i] != '$')
		decl->i++;
	if (!(*token)->flag && !decl->still)
		decl->n_t_v = ft_strjoin(decl->n_t_v,
				fmysubstr(t_v, decl->start, decl->i - decl->start));
	else
	{
		if (decl->still)
			add_middle_n(token,
				fmysubstr(t_v, decl->start, decl->i - decl->start));
		else
			(*token)->value = ft_strjoin((*token)->value,
					fmysubstr(t_v, decl->start, decl->i - decl->start));
	}
}

void	out_quotes_value(t_decl2 *decl, t_token **token)
{
	if (!is_white(decl->value[0]))
		not_w_first_i_2(decl, token);
	if (white_word(decl->value))
		decl->n_t_v = ft_strjoin(decl->n_t_v, decl->value);
	else
	{
		if (!(decl->n_t_v))
		{
			first_word_pos(decl->value, &decl->h, &decl->z);
			decl->n_t_v = fmysubstr(decl->value, decl->h, decl->z - decl->h);
		}
		add_middle(token, ft_mysplit(decl->value + decl->z, ' ', &decl->still));
	}
	if (!(*token)->flag && word_count(decl->value) > 1)
		(*token)->flag = 1;
}

void	out_quotes(t_decl2 *decl, char *t_v, t_token **token, t_params params)
{
	decl->start = decl->i;
	if (t_v[decl->i] == '$')
	{
		42 && (decl->z = 0, decl->i += 1);
		decl->start = decl->i;
		if (t_v[decl->i] && !is_alph(t_v[decl->i]) && t_v[decl->i] != '_')
			decl->i++;
		else
		{
			while (t_v[decl->i] && (is_alph_num(t_v[decl->i])
					|| t_v[decl->i] == '_'))
				decl->i++;
		}
		if (t_v[decl->start] == '?')
			decl->value = set_status(params.status);
		else
			decl->value = get_key(fmysubstr(t_v, decl->start,
						decl->i - decl->start), params.env);
		if (decl->value)
			out_quotes_value(decl, token);
		else
			decl->n_t_v = ft_strjoin(decl->n_t_v, "");
	}
	else
		out_quotes_not_key(decl, t_v, token);
}
