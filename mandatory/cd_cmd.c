/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:22:17 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/05/18 20:26:36 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	void	change_pwd_value(t_parse *st)
	{
		search_and_replace("OLDPWD", ft_copy(get_key("PWD", st->env)), &st, 1);
		search_and_replace("PWD", get_pwd(st), &st, 1);
	}

	t_env	*before_last_node(t_env *env)
	{
		while (env->next->next)
		env = env->next;
	return (env);
}

// void	sort_env(char **env)
// {
// 	char	**tmp;
// 	int		i;

// 	i = 0;
// 	tmp = env;
// 	while (tmp[i])
// 	{
// 		if (ft_strcmp(tmp[i], tmp[i + 1]) > 0)
// 		{
// 			ft_swap(&tmp[i], &tmp[i + 1]);
// 			tmp = env;
// 		}
// 		i++;
// 	}
// }
void sort_env(char **env)
{
    int sorted;
    int i;

    if (env == NULL)
        return;

    do {
        sorted = 1;
        for (i = 0; env[i + 1] != NULL; i++)
        {
            if (ft_strcmp(env[i], env[i + 1]) > 0)
            {
                ft_swap(&env[i], &env[i + 1]);
                sorted = 0;
            }
        }
    } while (!sorted);
}


void	ft_swap(char **a, char **b)
{
	char	*c;

	c = *a;
	*a = *b;
	*b = c;
}

void	just_export(t_parse *st)
{
	int i = 0;

	while (st->sorted_env[i])
	{
		printf("%s\n", st->sorted_env[i]); //remember to free  this shit on exit
		i++;
	}
}