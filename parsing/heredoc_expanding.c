#include "../minishell.h"

void	expand_line(char **line, t_params *params)
{
	t_decl2	decl;

	decl.n_t_v = NULL;
	decl.i = 0;
	while ((*line)[decl.i])
	{
		decl.start = decl.i;
		while ((*line)[decl.i] && (*line)[decl.i] != '$')
			decl.i++;
		decl.n_t_v = ft_strjoin(decl.n_t_v, ft_mysubstr(*line, decl.start, decl.i - decl.start));
		if ((*line)[decl.i])
			decl.i++;
		decl.start = decl.i;
		if (!is_alph((*line)[decl.i]) || (*line)[decl.i] != '_' || (*line)[decl.i] == '?')
			decl.i++;
		while ((*line)[decl.i] && (is_alph_num((*line)[decl.i]) || (*line)[decl.i] == '_'))
			decl.i++;
		if ((*line)[decl.start] == '?')
			decl.value = ft_strdup(ft_itoa(params->status));
		else
			decl.value = get_key(ft_mysubstr(*line, decl.start, decl.i - decl.start), params->env);
		if (decl.value)
			decl.n_t_v = ft_strjoin(decl.n_t_v, decl.value);
		else
			decl.n_t_v = ft_strjoin(decl.n_t_v, "");
	}
	*line = decl.n_t_v;
}
