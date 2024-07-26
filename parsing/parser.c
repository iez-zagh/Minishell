#include "../minishell.h"

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

void	initialize_parse(t_decl3 *decl, t_count *count, t_parse **new_parse, t_parse **parse)
{
	decl->i = 0;
	decl->l = 0;
	(*new_parse) = ft_malloc(sizeof(t_parse), 1);
	(*new_parse)->next = NULL;
	(*new_parse)->i = 0;
	(*new_parse)->files = NULL;
	(*new_parse)->in_fd = 0;
	if (decl->f_time)
		(*new_parse)->i = ++(*parse)->i;
	decl->f_time ++;
	(*new_parse)->cmd = ft_malloc((1 + count->words - count->in - count->out - count->app) * sizeof(char **), 1);
	(*new_parse)->in_dup = NULL;
	(*new_parse)->out_dup = NULL;
}

void parsing(t_token **tokens, t_parse **new_parse, t_decl3 *decl, t_params *params)
{
	while ((*tokens) && ft_strcmp((*tokens)->type, "PIPE") != 0)
	{
		if ((*tokens) && ft_strcmp((*tokens)->type, "WORD") == 0 && (!white_word((*tokens)->value) || (*tokens)->wh == 1))
			(*new_parse)->cmd[decl->i++] = ft_strdup((*tokens)->value);
		else if ((*tokens) && ft_strcmp((*tokens)->type, "INPUT") == 0)
			parse_input(tokens, new_parse);
		else if ((*tokens) && ft_strcmp((*tokens)->type, "OUTPUT") == 0)
			parse_output(tokens, new_parse);
		else if ((*tokens) && ft_strcmp((*tokens)->type, "APPEND") == 0)
			parse_append(tokens, new_parse);
		else if ((*tokens) && ft_strcmp((*tokens)->type, "HEREDOC") == 0)
			parse_heredoc(decl, tokens, new_parse, params);
		if ((*tokens))
			(*tokens) = (*tokens)->next;
	}
}

void	parser(t_token *tokens, t_parse **parse, t_params *params)
{
	t_parse	*new_parse;
	t_token	*copie;
	t_decl3	decl;
	t_count	count;

	copie = tokens;
	decl.f_time = 0;
	while (tokens)
	{
		count_things(&copie, &count);
		initialize_parse(&decl, &count, &new_parse, parse);
		parsing(&tokens, &new_parse, &decl, params);
		new_parse->cmd[decl.i] = NULL;
		add_back_parse(parse, new_parse);
		if (tokens)
			tokens = tokens->next;
	}
}
