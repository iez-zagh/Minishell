#include "../minishell.h"

void	comp(t_decl decl, t_token **token, char *token_value, int *i)
{
	if (decl.still)
		add_middle_n(token, ft_mysubstr(token_value,
				decl.first, *i - decl.first));
	else
		(*token)->value = ft_strjoin((*token)->value,
				ft_mysubstr(token_value, decl.first, *i - decl.first));
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
			*n_t_v = ft_strjoin(*n_t_v, ft_mysubstr(decl->value, 0, decl->j));
		else
		{
			if (decl->still)
				add_middle_n(token, ft_mysubstr(decl->value, 0, decl->j));
			else
				(*token)->value = ft_strjoin((*token)->value,
						ft_mysubstr(decl->value, 0, decl->j));
		}
		if (decl->value[decl->j] && no_rest(decl->value, decl->j))
			decl->still = 1;
		else
			decl->still = 0;
}
