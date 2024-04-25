/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:50:47 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/04/25 22:08:55 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <sys/stat.h>

# define RED_TEXT "\033[1;31m"
# define GREEN_TEXT "\033[1;32m"
# define YELLOW_TEXT "\033[1;33"
# define RESET_TEXT "\033[0m"
# define BLUE_TEXT "\033[1;34m"

typedef struct s_data
{
	char	**cmd;
}		t_data;

typedef struct t_var
{
	// name=hamza
	char	*var; // $name
	char	*value; // hamza
}		t_var;

typedef struct t_parse
{
	t_var			*myvar; // pointer to linked list of variables
	char			*arr;
	char			**cmd;// {"cat", NULL}  {"-l", NULL}
	char			*type;// command  flag  pipe  <  >  << || >> ...
	char			**com_arr;
	char			**paths_array;
	char			*env;
	char			*com_path;
	char			**env2;
	struct t_parse	*next;
}		t_parse;

char	*get_com_path(t_parse *st);
char	*get_acc_path(char **paths, char *com);
char	*get_path_variable(char **env);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
void	error(t_parse *st, int y);
void	signal_handler(int signum, t_parse *st);
void	wait_prompt(t_parse *st);
int		words_count(char const *s, char c);
char	*ft_cpy(char const *str, char c);
void	free_array(char **array);
char	**allocate_and_initialize_array(const char *s, char c, int w_count);
char	**ft_split(char const *s, char c);
void	excute_cmd(t_parse *st);
void	ft_free(char **s);
void	change_directory(t_parse *st);
void	excute_file(t_parse *st);
void	terminate_shell(t_parse *st);
int		ft_strcmp(const char *s1, const char *s2);
int		count_args(char **s);
int		numbered_args(char **s);

#endif