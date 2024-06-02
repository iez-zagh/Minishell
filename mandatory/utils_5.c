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

void	unset_cmd1(t_env **env, char *s)
{
	t_env	*tmp;
	t_env	*tmp2;
	
	tmp = *env;
	while (tmp->next)
	{
		if (!(ft_strcmp(tmp->next->key, s)))
		{
			tmp2 = tmp->next;
			tmp->next = tmp->next->next;
			free (tmp2->key);
			free (tmp2->value);
			free (tmp2);
			return ;
		}
		tmp = tmp->next;
	}
}

void	unset_cmd(t_parse *st)
{
	unset_cmd1(&(st->env), st->com_arr[1]);
	unset_cmd1(&(st->sorted_env), st->com_arr[1]);
}