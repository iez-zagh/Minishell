/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:58:53 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/07/21 14:53:42 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

size_t	ft_atol(char *s, t_parse *st, t_params *params)
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
			freeing(st, params);
			exit (255);
		}
	}
	return (res * sign);
}

void	ft_exit(t_parse *st, int args_n, t_params *params)
{
	size_t	n;

	if (args_n == 1)
	{
		// freeing(st, params);
		printf ("exit\n");
		exit (0);
	}
	if (args_n == 2 && !(numbered_arg(st->cmd[1])))
	{
		n = ft_atol(st->cmd[1], st, params);
		// freeing(st, params);
		printf ("exit\n");
		exit (n);
	}
}

void	empty_env(t_params *params)
{
	char	*pwd;
	char	*tmp;

	pwd = malloc (1024);
	params->env3 = malloc (sizeof(char *) * 5);
	if (!pwd || !params->env3)
		return ;
	params->env3[0] = ft_copy("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin");
	if (getcwd(pwd, 1024))
	{
		tmp = pwd;
		pwd = ft_strjoin2("PWD=", pwd);
		free (tmp);
		params->env3[1] = pwd;
	}
	else
		return ;
	params->env3[2] = ft_copy("SHLVL=1");
	params->env3[3] = ft_copy("_=/usr/bin/env");
	params->env3[4] = NULL;
}

int	checking_cmd2(t_parse *st, t_params *params)
{
	if (!ft_strcmp("env", st->cmd[0]))
	{
		if (env_cmd(st, params))
		{
			// ft_free2(st);
			return (1);
		}
	}
	return (0);
}

char	**copy_env(char **env)
{
	char	**res;
	int		i;

	res = malloc (sizeof(char *) * (count_args(env) + 1));
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
