#include "minishell.h"

void	ft_free2(t_parse *st)
{
	free(st->arr);
	ft_free(st->com_arr);
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

void	freeing(t_parse *st)
{
	free(st->path);
	free_list(st->env);
	if (st->com_arr)
		ft_free(st->com_arr);
	if (st->paths_array)
		ft_free(st->paths_array);
	ft_free(st->env2);
	free(st->arr);
	free (st);
}

void	freeing2(t_parse *st)
{
	// free(st->path);
	free(st->com_path);
	if (st->com_arr) 
		ft_free(st->com_arr);
	// if (st->paths_array)
	// 	ft_free(st->paths_array);
	free(st->arr);
}
	
void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free (s[i++]);
	free (s);
}
