#include "minishell.h"

int	check_syntax(char *s)
{
	int	i;

	i = 0;
	if (!((s[i] >= 'a' && s[i] <= 'z')
		|| (s[i] >= 'A' && s[i] <= 'Z') || (s[i] == '_')))
		return (1);
	// while (s[i])
	// {

	// }
	return (0);
}

void	pwd_cmd(t_parse *st)
{
	char	*pwd;

	pwd = get_pwd(st);
	printf("%s\n", pwd);
	free (pwd);
}

void	unset_cmd(t_parse *st, char *s)
{
	t_env	*tmp;
	t_env	*tmp2;
	
	tmp = st->env;
	while (tmp)
	{
		if (!(ft_strcmp(tmp->key, s)))
		{

		}
	}
}

void	delete_node(t_env *env)
{
	while (env)
	{
		
	}
}