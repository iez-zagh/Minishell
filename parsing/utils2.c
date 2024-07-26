#include "../minishell.h"

t_token	*last_node(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_parse	*last_node_parse(t_parse *parse)
{
	t_parse	*tmp;

	tmp = parse;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	add_back(t_token **token, t_token *new)
{
	if (!*token)
		*token = new;
	else
		last_node(*token)->next = new;
}

void	add_back_parse(t_parse **parse, t_parse *new)
{
	if (!*parse)
		*parse = new;
	else
		last_node_parse(*parse)->next = new;
}

void	tokens_reset(t_token **token)
{
	t_token	*tmp;

	while (*token)
	{
		tmp = *token;
		*token = (*token)->next;
		free(tmp->type);
		free(tmp->value);
		free(tmp);
	}
}

void	add_middle(t_token **token, char **arr)
{
	t_token	*tmp;
	t_token	*new;
	int		i;

	i = 0;
	while (arr[i])
	{
		new = ft_malloc(sizeof(t_token), 1);
		new->next = NULL;
		new->type = ft_strdup("WORD");
		new->value = ft_strdup(arr[i]);
		tmp = (*token)->next;
		(*token)->flag = 1;
		(*token)->next = new;
		new->next = tmp;
		*token = (*token)->next;
		i++;
	}
}

void	add_middle_n(t_token **token, char *value)
{
	t_token	*tmp;
	t_token	*new;

	new = ft_malloc(sizeof(t_token), 1);
	new->next = NULL;
	new->type = ft_strdup("WORD");
	new->value = value;
	if (white_word(value))
		new->wh = 1;
	tmp = (*token)->next;
	(*token)->flag = 1;
	(*token)->next = new;
	new->next = tmp;
	*token = (*token)->next;
}

void	exit_syntax_error(char *error_msg)
{
	printf("%s\n", error_msg);
}