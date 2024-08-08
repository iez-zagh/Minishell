/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:02:07 by houamrha          #+#    #+#             */
/*   Updated: 2024/08/06 14:54:52 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_sig(int sig)
{
	(void)sig;
	close(0);
}

void	count_things(t_token **tokens, t_count *count)
{
	count->in = 0;
	count->out = 0;
	count->app = 0;
	count->words = 0;
	if (*tokens && ft_strcmp((*tokens)->type, "PIPE") == 0)
		*tokens = (*tokens)->next;
	while (*tokens && ft_strcmp((*tokens)->type, "PIPE") != 0)
	{
		if (ft_strcmp((*tokens)->type, "WORD") == 0)
			count->words ++;
		else if (ft_strcmp((*tokens)->type, "INPUT") == 0)
			count->in ++;
		else if (ft_strcmp((*tokens)->type, "OUTPUT") == 0)
			count->out ++;
		else if (ft_strcmp((*tokens)->type, "APPEND") == 0)
			count->app ++;
		*tokens = (*tokens)->next;
	}
}

void	ini_pars(t_decl3 *decl, t_count *cn, t_parse **n_parse, t_parse **parse)
{
	decl->i = 0;
	decl->l = 0;
	(*n_parse) = ft_malloc(sizeof(t_parse), 1);
	(*n_parse)->next = NULL;
	(*n_parse)->i = 0;
	(*n_parse)->files = NULL;
	(*n_parse)->in_fd = 0;
	if (*parse)
		(*n_parse)->i = ++(*parse)->i;
	(*n_parse)->cmd = ft_malloc((1 + cn->words
				- cn->in - cn->out - cn->app) * sizeof(char **), 1);
	(*n_parse)->in_dup = NULL;
	(*n_parse)->out_dup = NULL;
}

int	parsing(t_token **tokens, t_parse **n_pars, t_decl3 *decl, t_params *params)
{
	while ((*tokens) && ft_strcmp((*tokens)->type, "PIPE") != 0)
	{
		if ((*tokens) && ft_strcmp((*tokens)->type, "WORD") == 0
			&& (!white_word((*tokens)->value) || (*tokens)->wh == 1))
			(*n_pars)->cmd[decl->i++] = ft_strdup((*tokens)->value);
		else if ((*tokens) && ft_strcmp((*tokens)->type, "INPUT") == 0)
			parse_input(tokens, n_pars);
		else if ((*tokens) && ft_strcmp((*tokens)->type, "OUTPUT") == 0)
			parse_output(tokens, n_pars);
		else if ((*tokens) && ft_strcmp((*tokens)->type, "APPEND") == 0)
			parse_append(tokens, n_pars);
		else if ((*tokens) && ft_strcmp((*tokens)->type, "HEREDOC") == 0)
		{
			if (!doc(decl, tokens, n_pars, params))
				return (0);
		}
		(*tokens) = (*tokens)->next;
	}
	return (1);
}

int	parser(t_token *tokens, t_parse **parse, t_params *params)
{
	t_parse	*new_parse;
	t_token	*copie;
	t_decl3	decl;
	t_count	count;

	signal(SIGINT, heredoc_sig);
	copie = tokens;
	while (tokens)
	{
		count_things(&copie, &count);
		ini_pars(&decl, &count, &new_parse, parse);
		if (!parsing(&tokens, &new_parse, &decl, params))
			return (0);
		new_parse->cmd[decl.i] = NULL;
		add_back_parse(parse, new_parse);
		if (tokens)
			tokens = tokens->next;
	}
	return (1);
}
