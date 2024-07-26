#include "../minishell.h"

void	ft_free2(t_parse *st)
{
	// free(st->arr);
	ft_free(st->cmd);
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

void	freeing(t_parse *st, t_params *params)
{
	free(params->path);
	free_list(params->env);
	free_list(params->sorted_env);
	if (st->cmd)
		ft_free(st->cmd);
	if (params->paths_array)
		ft_free(params->paths_array);
	ft_free(params->env2);
	free (st);
}

void	freeing2(t_parse *st)
{
	// free(params->path);
	free(st->com_path);
	if (st->cmd)
		ft_free(st->cmd);
	// if (params->paths_array)
	// 	ft_free(params->paths_array);
}

void	ft_free(char **s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		free (s[i++]);
	free (s);
}

int	back_cmd(t_parse *st, int i, t_params *params)
{
	printf("%d\n", i);
	if (ft_strcmp("..", st->cmd[1]))
		return (1);
	if (chdir("..") == -1)
	{
		printf ("problem in chdir func\n"); //needs protection 
		exit (1);
	}
	change_pwd_value(params);
	return (0);
}
