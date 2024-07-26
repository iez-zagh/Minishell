/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:50:33 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/07/25 18:32:36 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

int	main(int __attribute__((unused)) argc, char __attribute__((unused)) * argv[], char *env[])
{
	t_params	params;

	// atexit(leaks);
	if (!env || !env[0])
	 	empty_env(&params); //return double char pointer
	else
		params.env3 = copy_env(env);
	params.env = set_env(params.env3);
	params.path = ft_copy(get_key("PATH", params.env));
	params.paths_array = ft_split(params.path, ':');
	params.sorted_env = set_env(params.env3);// the ctrl+c status=130 remember
	sort_env(params.sorted_env);
	ft_free(params.env3);
	update(&params);
	params.env2 = list2array(params.env,  &params);
	wait_prompt1(&params);
}

void	error(t_parse *st, int y, t_params *params)
{
	if (y == 1)
		printf("an error accored in the forking operation !\n");
	else if (y == 2)
		printf("allocation failure\n");
	else if (y == 3)
		ft_free(params->paths_array);
	else if (y == 4)
		printf("%s :command not found\n", st->cmd[0]);
	else if (y == 5)
		printf("exit\nShellantics: exit: %s: numeric argument required\n", st->cmd[1]);
	else if (y == 6)
		printf("error while geting working path\n");
	else if (y == 7)	
		printf("something went wrong !\n");
	exit(1);
}

void	ft_join(char **res, t_params *params)
{
	char	*res1;
	char	*res2;

	res1 = get_key(res[0], params->env);
	if (!res1)
		return ;
	res2 = ft_strjoin2(res1, res[1]);
	free (res[1]);
	res[1] = res2;
}
