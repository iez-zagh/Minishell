/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:03:24 by houamrha          #+#    #+#             */
/*   Updated: 2024/08/06 12:02:15 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_type1(char *line, int *i)
{
	if (line[*i] == '|')
		return ((*i)++, ft_strdup("PIPE"));
	else if (line[*i] == '<' && line[*i + 1] == '<')
		return ((*i) += 2, ft_strdup("HEREDOC"));
	else if (line[*i] == '>' && line[*i + 1] == '>')
		return ((*i) += 2, ft_strdup("APPEND"));
	else if (line[*i] == '<')
		return ((*i)++, ft_strdup("INPUT"));
	else if (line[*i] == '>')
		return ((*i)++, ft_strdup("OUTPUT"));
	else if (is_white(line[*i]))
	{
		while (is_white(line[*i]))
			(*i)++;
		return (ft_strdup("WHITE"));
	}
	else
		return (NULL);
}

void	quote_toggle(int *in_quote, char *quote, int i, char *line)
{
	if (*in_quote && line[i] == *quote)
		*in_quote = 0;
	else if (!*in_quote)
	{
		*quote = line[i];
		*in_quote = 1;
	}
}

char	*get_type2(char *line, int *i, t_params *params)
{
	char	*type;
	int		in_quote;
	char	quote;

	42 && (in_quote = 0, type = ft_strdup("WORD"));
	while (line[*i])
	{
		if (line[*i] == '\'' || line[*i] == '"')
			quote_toggle(&in_quote, &quote, *i, line);
		if (in_quote)
			(*i)++;
		else
		{
			if (is_in_word(line[*i]))
				(*i)++;
			else
				break ;
		}
	}
	if (in_quote)
	{
		syntax_error("unclosed quotes syntax error", params);
		params->q = 1;
	}
	return (type);
}

void	init_token(t_token *new_token, char *line, int *i, t_params *params)
{
	char	*type;
	int		start;

	type = get_type1(line, i);
	if (type)
		new_token->value = ft_strdup("operator");
	else
	{
		start = *i;
		type = get_type2(line, i, params);
		new_token->value = fmysubstr(line, start, (*i) - start);
	}
	new_token->type = type;
}

void	tokenize(t_token **token, char *line, t_params *params)
{
	int		i;
	t_token	*new_token;

	if (white_word(line))
		return ;
	i = 0;
	while (line[i])
	{
		new_token = ft_malloc(sizeof(t_token), 1);
		init_token(new_token, line, &i, params);
		new_token->next = NULL;
		new_token->wh = 0;
		new_token->here = 0;
		add_back(token, new_token);
	}
}
