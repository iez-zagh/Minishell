/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:59:33 by houamrha          #+#    #+#             */
/*   Updated: 2024/08/06 16:14:34 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	is_in_quote(t_decl2 *decl, char *t_v)
{
	decl->z = 0;
	if ((t_v[decl->i] == '\'' || t_v[decl->i] == '"') && !decl->in_quote)
	{
		decl->in_quote = 1;
		decl->quote = t_v[decl->i];
		decl->i++;
	}
	else if (decl->in_quote && decl->quote == t_v[decl->i])
	{
		decl->i += 1;
		decl->in_quote = 0;
	}
}

void	inside_single_quote(t_decl2 *decl, t_token **token, char *t_v)
{
	decl->start = decl->i;
	while (t_v[decl->i] && t_v[decl->i] != '\'')
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

void	double_quote_key(t_decl2 *decl, char *t_v, t_params params)
{
	decl->i += 1;
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
	{
		if (g_status == 2)
			decl->value = ft_strdup(ft_itoa(1));
		else
			decl->value = ft_strdup(ft_itoa(params.status));
	}
	else
		decl->value = get_key(fmysubstr(t_v, decl->start,
					decl->i - decl->start), params.env);
	if (decl->value)
		decl->n_t_v = ft_strjoin(decl->n_t_v, decl->value);
	else
		decl->n_t_v = ft_strjoin(decl->n_t_v, "");
}

void	in_quotes(t_decl2 *decl, char *t_v, t_token **token, t_params params)
{
	if (decl->quote == '\'')
		inside_single_quote(decl, token, t_v);
	else
	{
		if (t_v[decl->i] == '$')
			double_quote_key(decl, t_v, params);
		else
		{
			decl->start = decl->i;
			while (t_v[decl->i] && t_v[decl->i] != '"' && t_v[decl->i] != '$')
				decl->i++;
			if (!(*token)->flag && !decl->still)
				decl->n_t_v = ft_strjoin(decl->n_t_v,
						fmysubstr(t_v, decl->start, decl->i - decl->start));
			else
			{
				if (decl->still)
					add_middle_n(token, fmysubstr(t_v,
							decl->start, decl->i - decl->start));
				else
					(*token)->value = ft_strjoin((*token)->value,
							fmysubstr(t_v, decl->start, decl->i - decl->start));
			}
		}
	}
}

void	quotes_expander(t_token **token, char *t_v, t_params params)
{
	t_decl2	decl;
	t_token	*tmp;

	decl.n_t_v = NULL;
	decl.in_quote = 0;
	decl.i = 0;
	decl.j = 0;
	decl.still = 0;
	tmp = *token;
	while (t_v[decl.i])
	{
		is_in_quote(&decl, t_v);
		if (decl.in_quote)
			in_quotes(&decl, t_v, token, params);
		else
			out_quotes(&decl, t_v, token, params);
	}
	tmp->value = decl.n_t_v;
	if (white_word(tmp->value))
	{
		tmp->flag = 1;
		tmp->wh = 1;
	}
}
