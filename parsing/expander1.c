#include "../minishell.h"

void	valide_val(t_decl *decl, char **n_t_v, t_token **token)
{
	if (!is_white(decl->value[0]))
		not_w_first_i(decl, n_t_v, token);
	if (white_word(decl->value))
		*n_t_v = ft_strjoin(*n_t_v, ft_strdup(decl->value));
	else
	{
		if (!(*n_t_v))
		{
			first_word_pos(decl->value, &decl->i, &decl->j);
			*n_t_v = ft_mysubstr(decl->value, decl->i, decl->j - decl->i);
		}
		add_middle(token, ft_mysplit(decl->value + decl->j, ' ', &decl->still));
	}
	if (!(*token)->flag && word_count(decl->value) > 1)
		(*token)->flag = 1;
}

void	get_value(t_decl *decl, int *i, char *token_value, int status)
{
	decl->j = 0;
	(*i)++;
	decl->first = *i;
	if (token_value[*i] && !is_alph(token_value[*i]) && token_value[*i] != '_')
 		(*i)++;
	else
	{
		while (token_value[*i] && token_value[*i] != '$'
			&& (is_alph_num(token_value[*i]) || token_value[*i] == '_'))
			(*i)++;
	}
	if (token_value[decl->first] == '?')
		decl->value = ft_strdup(ft_itoa(status));
	else
		decl->value = get_key(ft_mysubstr(token_value,
				decl->first, (*i) - decl->first), decl->env);
}

void	set_value(char **n_t_v, char *token_value, int *i, t_token **token)
{
	t_decl	decl;

	decl.still = 0;
	decl.env = (*token)->env;
	while (token_value[*i])
	{
		if (token_value[*i] == '$')
		{
			get_value(&decl, i, token_value, (*token)->status);
			if (!decl.value)
				*n_t_v = ft_strjoin(*n_t_v, "");
			else
				valide_val(&decl, n_t_v, token);
		}
		else
		{
			decl.first = *i;
			while (token_value[*i] && token_value[*i] != '$')
				(*i)++;
			if (!(*token)->flag && !decl.still)
				*n_t_v = ft_strjoin(*n_t_v, ft_mysubstr(token_value,
							decl.first, *i - decl.first));
			else
				comp(decl, token, token_value, i);
		}
	}
}

void	non_quotes_expander(t_token **token, t_params params)
{
	int		i;
	char	*n_t_v;
	t_token	*tmp;

	(*token)->status = params.status;
	i = 0;
	n_t_v = NULL;
	tmp = *token;
	while ((*token)->value[i] && (*token)->value[i] != '$')
		i++;
	if (i)
		n_t_v = ft_mysubstr((*token)->value, 0, i);
	(*token)->env = params.env;
	if ((*token)->value[i])
		set_value(&n_t_v, (*token)->value, &i, token);
	tmp->value = n_t_v;
	if (white_word(tmp->value))
		tmp->flag = 1;
}

void	expander(t_token *token, t_params params)
{
	while (token)
	{
		token->flag = 0;
		if (ft_strcmp(token->type, "WORD") == 0 && !token->here && in_str(token->value, '$'))
		{
			if (in_str(token->value, '\'') || in_str(token->value, '"'))
				quotes_expander(&token, token->value, params);
			else
				non_quotes_expander(&token, params);
		}
		else
		{
			token->wh = 1;
			quotes_removal(token);
		}
		token = token->next;
	}
}
