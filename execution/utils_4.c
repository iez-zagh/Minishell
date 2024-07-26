#include "../minishell.h"

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

void	check_join(char **s, t_parse *st, t_params *params)
{
	int	i;

	i = 0;
	params->export_f = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == '=')
			if ((*s)[i - 1] == '+')
			{
				params->export_f = 1;
				ft_join_value(s, st, params);
				return ;
			}
		i++;
	}
}

void	ft_join_value(char **s, t_parse *st, t_params *params)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc (ft_strlen(*s));
	if (!res)
		error(st, 2, params); //more portection
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
	*s = res;
}

void	free_update(char **res, t_params *params)
{
	free (res);
	ft_free(params->env2);
	params->env2 = list2array(params->env, params);
	free(params->path);
	params->path = ft_copy(get_key("PATH", params->env)); //handle empty path or else
	ft_free(params->paths_array);
	if (!params->path)
	{
		params->paths_array = NULL;
		return ;
	}
	params->paths_array = ft_split(params->path, ':');
}

char	**export_checker(char *s)
{
	int		i;
	char	**res;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	res = malloc (sizeof(char *) * (3));
	res[0] = malloc (i + 1);
	if (!res || !res[0])
		return (NULL);//need more protection
	i = 0;
	while (s[i] && s[i] != '=')
	{
		res[0][i] = s[i];
		i++;
	}
	res[0][i++] = '\0';
	return (export_checker2(res, s, i));
}

char	**export_checker2(char **res, char *s, int i)
{
	if (i < (int)ft_strlen(s))
	{
		res[1] = ft_copy(&s[i]);
		res[2] = NULL;
	}
	else
		res[1] = NULL;//possible a leak here be carefull
	return (res);
}
