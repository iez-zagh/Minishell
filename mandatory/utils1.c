/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:23:49 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/05/06 16:19:17 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join_string;
	char	*join;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	join_string = (char *)malloc
		((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!join_string)
		return (0);
	join = join_string;
	while (*s1)
	{
		*join = *s1;
		join++;
		s1++;
	}
	while (*s2)
	{
		*join = *s2;
		join++;
		s2++;
	}
	*join = '\0';
	return (join_string);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 && *s2 && (n - 1) > 0
		&& *(unsigned char*)s1 == *(unsigned char*)s2)
	{
		s1++;
		s2++;
		n--;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

char	*get_path_variable(char **env)
{
	char	*s;
	int		i;

	s = "PATH";
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(s, env[i], 4) == 0)
			return (env[i]);
		i++;
	}
	return (NULL);
}

char	*get_acc_path(char **paths, char *com)
{
	int		i;
	char	*r;
	char	*rr;

	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		r = ft_strjoin(paths[i], "/");
		rr = ft_strjoin(r, com);
		free(r);
		if (access(rr, F_OK | X_OK) == 0)
			return (rr);
		i++;
		free(rr);
	}
	return (NULL);
}

char	*get_com_path(t_parse *st)
{
	char *com_path = get_acc_path(st->paths_array, st->arr);
	return (com_path);
}
