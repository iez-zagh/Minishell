/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:58:53 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/05/09 13:23:01 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	numbered_arg(char *s)
{
	int	i;

	i = 0;
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
		if (res > __LONG_MAX__)
			error(st, 5);
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
