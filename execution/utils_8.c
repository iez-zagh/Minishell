/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:41:03 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/06 11:17:08 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_number(char *s, int i)
{
	int	res;

	res = 0;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (-1);
		res = res * 10 + s[i] - '0';
		if (res == 100)
			return (-1);
		i++;
	}
	return (res);
}

int	ft_shell_atoi(char *s)
{
	int	i;
	int	res;

	if (!s)
		return (-1);
	res = 0;
	i = 0;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
		{
			if (s[i + 1] >= '0' && s[i + 1] <= '9')
				return (-2);
			else
				return (-1);
		}
		else
			i++;
	}
	return (get_number(s, i));
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
	if (!NULL)
		return (NULL);
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

void	change_pwd(t_params *params, char *tmp, int *i)
{
	change_pwd_value(params);
	free (tmp);
	*i = 0;
}

int	just_echo(t_parse *st)
{
	if (!st->cmd[1])
		return (write(1, "\n", 1), 0);
	return (0);
}
