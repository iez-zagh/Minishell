/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:58:53 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/06/02 18:27:01 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	numbered_arg(char *s)
{
	int	i;
	
	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_atol(char *s, t_parse *st)
{
	int		i;
	size_t	res;
	int		sign;

	i = 0;
	sign = 1;
	res = 0;
	if (s[0] == '-' || s[0] == '+')
	{
		if (s[0] == '-')
			sign = -1;
		i++;
	}
	while(s[i])
	{
		res = res * 10 + s[i++] - '0';
		if (!(s[i] >= 0 && s[i] <= '9') || res > __LONG_MAX__)
		{
			freeing(st);
			exit (255);
		}
	}
	return (res * sign);
}

void	ft_exit(t_parse *st, int args_n)
{
	size_t	n;

	if (args_n == 1)
	{
		freeing(st);
		printf ("exit\n");
		exit (0);
	}
	if (args_n == 2 && !(numbered_arg(st->com_arr[1])))
	{
		n = ft_atol(st->com_arr[1], st);
		freeing(st);
		printf ("exit\n");
		exit (n);
	}
}

void	empty_env(t_parse *st)
{
	char	*pwd;
	char	*tmp;
	
	pwd = malloc (1024);
	st->env3 = malloc (sizeof(char *) * 5);
	if (!pwd || !st->env3)
		return ;
	st->env3[0] = ft_copy("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin");
	if (getcwd(pwd, 1024))
	{
		tmp = pwd;
		pwd = ft_strjoin("PWD=", pwd);
		free (tmp);
		st->env3[1] = pwd;
	}
	else
		return ;
	st->env3[2] = ft_copy("SHLVL=1");
	st->env3[3] = ft_copy("_=/usr/bin/env");
	st->env3[4] = NULL;
}

int	checking_cmd2(t_parse *st)
{
	if (!ft_strcmp(st->com_arr[0], ".."))
	{
		printf("%s: command not found\n",st->com_arr[0]);
		ft_free2(st);
		return (1);
	}
	if (ft_strncmp(st->com_arr[0], "cd", 2) == 0)
	{
		change_directory(st);
		ft_free2(st);
		return (1);
	}
	if (!ft_strcmp(st->com_arr[0], "export"))
	{	
		export_cmd1(st);
		ft_free2(st);
		return (1);
	}
	if (!ft_strcmp(st->com_arr[0], "pwd")) // enter with deleted directory
	{
		pwd_cmd(st);
		ft_free2(st);
		return (1);	
	}
	return (0);
}

char	**copy_env(char **env)
{
	char	**res;
	int		i;

	res = malloc (sizeof(char *) * count_args(env) + 1);
	if (!res)
		return (NULL);//more protection
	i = 0;
	while (env[i])
	{
		res[i] = ft_copy(env[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}