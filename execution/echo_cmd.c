/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:43:44 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/07 12:47:30 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	trying_with_pwd(t_params *params)
{
	char	*pwd;

	pwd = malloc(1024 * (sizeof(char)));
	if (!pwd)
		malloc_error(params);
	getcwd(pwd, 1024);
	if (!pwd)
	{
		write(2, "some thing went wrong here\n", 28);
		params->status = 1;
		free (pwd);
		return (1);
	}
	else
	{
		search_and_replace(ft_copy("PWD"), pwd, &(params->env), 0);
		search_and_replace(ft_copy("PWD"), ft_copy(pwd),
			&(params->sorted_env), 0);
	}
	return (0);
}

void	change_pwd2(char *tmp2, t_params *params, char *tmp)
{
	if (access(tmp2, F_OK) != -1)
	{
		search_and_replace(ft_copy("PWD"), ft_copy(tmp2), &(params->env), 0);
		search_and_replace(ft_copy("PWD"),
			ft_copy(tmp2), &(params->sorted_env), 0);
	}
	else
	{
		search_and_replace(ft_copy("PWD"),
			ft_strjoin2(tmp, "/.."), &(params->env), 0);
		search_and_replace(ft_copy("PWD"),
			ft_strjoin2(tmp, "/.."), &(params->sorted_env), 0);
	}
	free (tmp);
}

int	check_deleted(t_params *params, char *tmp2)
{
	struct stat	the_path;
	char		*tmp;

	tmp = ft_copy(get_key("PWD", params->env));
	if (!tmp)
		return (0);
	stat(tmp, &the_path);
	if (!S_ISDIR(the_path.st_mode))
	{
		chdir("..");
		write(2, "cd: error retrieving current ", 29);
		write(2, "directory: getcwd\n", 18);
		search_and_replace(ft_copy("OLDPWD"),
			ft_copy(get_key("PWD", params->env)), &(params->env), 0);
		search_and_replace(ft_copy("OLDPWD"),
			ft_copy(get_key("PWD", params->env)), &(params->sorted_env), 0);
		change_pwd2(tmp2, params, tmp);
		return (1);
	}
	return (0);
}

char	*ft_spliter(char *s, int j, t_params *params)
{
	int		i;
	char	*pwd;
	char	*pwd2;

	(void)j;
	if (!s)
		return (NULL);
	pwd = malloc(1024);
	if (!pwd)
		malloc_error(params);
	if (!getcwd(pwd, 1024))
		return (free(pwd), ft_copy(get_key("PWD", params->env)));
	i = 0;
	i = ft_strlen(pwd) - 1;
	while (pwd[i] && (pwd[i] != '/'))
		i--;
	pwd2 = ft_substr(pwd, 0, i);
	return (free(pwd), pwd2);
}

int	change_dir(t_parse *st, t_params *params, char *s)
{
	struct stat	the_path;
	char		*tmp;
	static int	i = 0;

	stat(s, &the_path);
	tmp = ft_spliter(get_key("PWD", params->env), i, params);
	if (!tmp)
	{
		if (trying_with_pwd(params))
			return (1);
		return (change_dir(st, params, s));
	}
	if (access(tmp, F_OK) == -1 && !(ft_strcmp("..", st->cmd[1])))
		return (check_deleted(params, tmp), i++, free(tmp), 1);
	else if (S_ISDIR(the_path.st_mode) && access(s, X_OK) == -1)
		return (print_error("cd", ": Permission denied\n", s), free(tmp), 1);
	else if (!S_ISDIR(the_path.st_mode) && access(s, F_OK) != -1)
		return (print_error("cd", ": not a directory\n", s), free(tmp), 1);
	else if (chdir(s) == -1)
		return (print_error("cd",
				": no such file or directory\n", s), free(tmp), 1);
	else
		change_pwd(params, tmp, &i);
	return (0);
}
