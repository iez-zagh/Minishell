#include "minishell.h"

int ft_strchr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	check_join(char **s, t_parse *st)
{
	int	i;

	i = 0;
	st->export_f = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == '=')
			if ((*s)[i - 1] == '+')
			{
				st->export_f = 1;
				ft_join_value(s, st);
				return ;
			}
		i++;
	}
}

void	ft_join_value(char **s, t_parse *st)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc (ft_strlen(*s));
	if (!res)
		error(st, 2); //more portection
	while ((*s)[i])
	{
		if ((*s)[i] == '+')
		{
			i++;
			continue;
		}
		res[j++] = (*s)[i++];
	}
	res[j] = '\0';
	free(*s);
	*s = res;
}

void	free_update(char **res, t_parse *st)
{
	free (res);
	ft_free(st->env2);
	st->env2 = list2array(st->env, st);
	free(st->path);
	st->path = ft_copy(get_key("PATH", st->env)); //handle empty path or else
	ft_free(st->paths_array);
	st->paths_array = ft_split(st->path, ':');
}

char	**export_checker(char *s)
{
	int		i;
	char	**res;

	i = 0;

	while (s[i] && s[i] != '=')
		i++;
	res = malloc (sizeof(char *) * 2 + 1);
	res[0] = malloc (i + 1);
	if (!res || !res[0])
		return (NULL);//need more protection
	i = 0;
	while (s[i] && s[i] != '=')
	{
		res[0][i] = s[i];
		i++;
	}
	i++;
	res[1] = ft_copy(&s[i]);
	return (res);
}
