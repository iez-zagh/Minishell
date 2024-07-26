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

void	parse_heredoc(t_decl3 *decl, t_token **tokens, t_parse **new_parse, t_params *params)
{
	(*new_parse)->i ++;
	if (ft_strcmp((*tokens)->next->type, "WHITE") == 0)
		(*tokens) = (*tokens)->next;
	(*new_parse)->in_dup = ft_strjoin("/tmp/h", ft_itoa((*new_parse)->i));
	decl->fd = open(ft_strjoin("/tmp/h", ft_itoa((*new_parse)->i)), O_CREAT | O_RDWR | O_TRUNC, 0777);
	while(1)
	{
		decl->line = readline("> ");
		if (!decl->line)
			break;
		if (ft_strcmp((*tokens)->next->value, decl->line) == 0)
		{
			free(decl->line);
			break;
		}
		if (!(*tokens)->next->has_q && in_str(decl->line, '$'))
			expand_line(&decl->line, params);
		write(decl->fd, decl->line, ft_strlen(decl->line));
		write(decl->fd, "\n", 1);
		free(decl->line);
	}
	close(decl->fd);
	(*tokens) = (*tokens)->next;
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

