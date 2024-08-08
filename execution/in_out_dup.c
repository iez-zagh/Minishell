/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:24:39 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/07 18:13:31 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_perms(char *s, int type)
{
	int			fd;
	struct stat	path;

	fd = 0;
	stat(s, &path);
	if (type != 1 && S_ISDIR(path.st_mode))
		return (print_error(NULL, ": is a directory\n", s), 1);
	if (access(s, R_OK) == -1 && access(s, F_OK) != -1)
		return (print_error(NULL, ": Permission denied\n", s), 1);
	if (type == 1)
		fd = open(s, O_RDONLY);
	if (fd && fd == -1)
		return ((print_error(NULL, ": No such file or directory\n",
					s)), 1);
	if (fd)
		close (fd);
	return (0);
}

int	excute_cmd_dup(t_parse *st, t_params *params, int fd)
{
	if (fd != -2)
	{
		params->stdin_ = dup(STDIN_FILENO);
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror ("dup2");
			close (fd);
			return (1);
		}
		close (fd);
	}
	if (st->out_fd != -2)
	{
		params->stdout_ = dup(STDOUT_FILENO);
		if (dup2(st->out_fd, STDOUT_FILENO) == -1)
		{
			perror ("dup2");
			close (st->out_fd);
			return (1);
		}
		close (st->out_fd);
	}
	return (0);
}

int	get_type(t_files *files, char *s)
{
	while (files)
	{
		if (!(ft_strcmp(files->file, s)))
			return (files->type);
		files = files->next;
	}
	return (0);
}

int	open_files(t_parse *st, t_params *params)
{
	t_files	*file;
	int		out;

	1 && (out = -1, file = st->files);
	while (file)
	{
		if (check_perms(file->file, file->type))
			return (1);
		if (file->is_amb)
			return (write(2, "shellantics: ambiguous redirect\n", 32),
				close(st->in_fd), params->status = 1, 1);
		if (file->type == 2)
			st->out_fd = open(file->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file->type == 3)
			st->out_fd = open(file->file, O_WRONLY | O_CREAT
					| O_APPEND, 0644);
		if (file->type != 1 && !ft_strcmp(file->file, st->out_dup))
			out = file->type;
		close (st->out_fd);
		file = file->next;
	}
	if (open_fs(st, out))
		return (1);
	return (0);
}

int	in_out_dup(t_parse *st, t_params *params)
{
	st->in_fd = -2;
	st->out_fd = -2;
	if (open_files(st, params))
	{
		if (!params->pid)
			exit (1);
		return (1);
	}
	if (!st->cmd || !st->cmd[0])
	{
		if (!params->pid)
			exit (0);
	}
	excute_cmd_dup(st, params, st->in_fd);
	return (0);
}
