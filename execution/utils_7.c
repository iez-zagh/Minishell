#include "../minishell.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*join_string;
	char	*join;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (!s1)
		s1 = ft_strdup2("");
	join_string = malloc
		((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (join_string == 0)
		return (0);
	join = join_string;
	while (*s1)
	{
		*join = *s1;
		join++;
		s1++;
	}
	while (*s2)
	{
		*join = *s2;
		join++;
		s2++;
	}
	*join = '\0';
	return (join_string);
}

char	*ft_strdup2(const char *s1)
{
	char		*copy;
	char		*c;
	const char	*s;
	int			i;

	i = 0;
	s = s1;
	while (*s)
	{
		i++;
		s++;
	}
	copy = malloc(i * sizeof(char) + 1);
	if (copy == NULL)
		return (0);
	c = copy;
	while (*s1)
	{
		*c = *s1;
		c++;
		s1++;
	}
	*c = '\0';
	return (copy);
}

void	update_(t_parse *st, t_params *params)
{
	if (!st->cmd)
		return ;
	if (!st->cmd[0])
	{
		search_and_replace("_", ft_copy(""), &(params->env), 1);
	}
	else if (st->cmd[0] && (ft_strcmp(st->cmd[0], "echo")))
	{
		search_and_replace("_", ft_copy(st->cmd[count_args(st->cmd) - 1]), &(params->env), 1);
	}
}

