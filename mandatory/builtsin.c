/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtsin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 20:05:53 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/05/06 20:58:34 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_env(char *s1, char *s2)
{
	char	*join_string;
	char	*join;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	join_string = (char *)malloc
		((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (!join_string)
		return (0);
	join = join_string;
	while (*s1)
	{
		*join = *s1;
		join++;
		s1++;
	}
	*join = '=';
    join++;
	while (*s2)
	{
		*join = *s2;
		join++;
		s2++;
	}
	*join = '\0';
	return (join_string);
}
