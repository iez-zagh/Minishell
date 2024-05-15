#include "minishell.h"

int	count_args(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	freeing(t_parse *st)
{
	free_list(st->env);
	ft_free(st->com_arr);
	ft_free(st->paths_array);
	ft_free(st->env2);
	free(st->arr);
	free (st);
}

void	free_list(t_env *env)
{
	t_env	*tmp;
	
	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free (env);
		env = tmp;
	}
}