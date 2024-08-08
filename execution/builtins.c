/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:43:35 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/07 13:01:12 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_args(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	print_error(char *cmd, char *s, char *folder)
{
	write (2, "shellantics: ", 13);
	if (cmd)
		write (2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	if (folder)
		write (2, folder, ft_strlen(folder));
	write (2, s, ft_strlen(s));
}

int	unset_cmd(t_parse *st, t_params *params)
{
	int	i;

	i = 1;
	while (st->cmd[i])
	{
		if (check_syntax(st->cmd[i]))
		{
			print_error("env", ": not a valid identifier\n", st->cmd[i]);
			params->status = 1;
		}
		else if (!ft_strcmp("_", st->cmd[i]))
			params->status = 0;
		else
		{
			unset_cmd1(&(params->env), st->cmd[i]);
			unset_cmd1(&(params->sorted_env), st->cmd[i]);
			params->status = 0;
		}
		i++;
	}
	free_update(NULL, params);
	return (params->status);
}
