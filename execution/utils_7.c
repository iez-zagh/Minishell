/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:59:22 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/07 17:12:27 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (!join_string)
		return (NULL);
	join = join_string;
	while (*s1)
		*join++ = *s1++;
	while (*s2)
		*join++ = *s2++;
	*join = '\0';
	return (join_string);
}

void	update_(t_parse *st, t_params *params)
{
	params->stdin_ = -1;
	params->stdout_ = -1;
	g_status = 0;
	if (!st->cmd)
		return ;
	if (!st->cmd[0])
	{
		search_and_replace(ft_copy("_"), ft_copy(""), &(params->env), 0);
	}
	else if (st->cmd[0] && (ft_strcmp(st->cmd[0], "echo")))
	{
		search_and_replace(ft_copy("_"),
			ft_copy(st->cmd[count_args(st->cmd) - 1]),
			&(params->env), 0);
	}
}

int	check_builtins(char *s)
{
	if (!s)
		return (0);
	if (!(ft_strcmp(s, "cd")) || !(ft_strcmp(s, "export"))
		|| !(ft_strcmp(s, "unset"))
		|| !(ft_strcmp(s, "env")) || !(ft_strcmp(s, "exit"))
		||!(ft_strcmp(s, "pwd"))
		||!(ft_strcmp(s, "echo")))
		return (1);
	return (0);
}

char	**export_checker(char *s, t_params *params)
{
	int		i;
	char	**res;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	res = ft_malloc (sizeof(char *) * (3), 1);
	res[0] = ft_malloc (i + 1, 1);
	if (!res || !res[0])
		malloc_error(params);
	i = 0;
	while (s[i] && s[i] != '=')
	{
		res[0][i] = s[i];
		i++;
	}
	res[0][i++] = '\0';
	return (export_checker2(res, s, i));
}

int	checking_cmd3(t_parse *st, t_params *params)
{
	if (!ft_strcmp(st->cmd[0], "pwd"))
		return (pwd_cmd(params));
	if (!ft_strcmp(st->cmd[0], "unset"))
		return (unset_cmd(st, params));
	if (ft_strcmp(st->cmd[0], "cd") == 0)
		return (change_directory(st, params));
	if (ft_strcmp(st->cmd[0], "echo") == 0)
		return (echo_cmd(st));
	return (0);
}
