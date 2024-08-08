/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 23:04:19 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/04 11:59:43 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalpha(int a)
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
		return (1);
	return (0);
}

int	ft_digit(int a)
{
	if (a >= '0' && a <= '9')
		return (1);
	return (0);
}

int	check_syntax(char *s)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(s[i])) && (s[i] != '_'))
		return (1);
	i++;
	while (s[i])
	{
		if (s[i + 1] == '+' && !s[i + 1])
			return (0);
		if (!ft_isalpha(s[i]) && (s[i] != '_') && !ft_digit(s[i]))
			return (1);
		i++;
	}
	return (0);
}

int	exec_echo(int i, t_parse *st)
{
	int	j;

	j = i;
	while (st->cmd[i])
	{
		write(1, st->cmd[i], ft_strlen(st->cmd[i]));
		i++;
		if (st->cmd[i])
			write(1, " ", 1);
	}
	if (j == 1)
		write(1, "\n", 1);
	return (0);
}

int	echo_cmd(t_parse *st)
{
	int	i;
	int	j;

	if (count_args(st->cmd) == 1)
		return (just_echo(st));
	i = 1;
	while (st->cmd[i])
	{
		if (st->cmd[i][0] != '-')
			return (exec_echo(i, st));
		j = 1;
		while (st->cmd[i][j])
		{
			if (st->cmd[i][j] != 'n')
				return (exec_echo(i, st));
			j++;
		}
		i++;
	}
	return (0);
}
