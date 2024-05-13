/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:50:47 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/05/13 11:31:51 by iez-zagh         ###   ########.fr       */
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

typedef struct t_env
{
	// name=hamza
	char		*key; // $name
	char		*value; // hamza
	struct t_env *next;
}		t_env;

// {
// 	char **cmd;
// 	char **in;
// 	char **out;
// 	char **app;
// }

typedef struct t_parse
{
	// t_var			*env; // pointer to linked list of variables
	char			*arr;
	// char			**cmd;// {"cat", NULL}  {"-l", NULL}
	// t_data			*h;
	char			*type;// command  flag  pipe  <  >  << || >> ...
	char			**com_arr;
	char			**paths_array;
	char			*path;
	char			*com_path;
	char			**env2;
	t_env			*env;
	int				exit_status;
}		t_parse;

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
int		numbered_arg(char *s);
void	freeing(t_parse *st);
size_t	ft_atol(char *s, t_parse *st);
void	ft_exit(t_parse *st, int args_n);
int		checking_cmd(t_parse *st);
void	set_env(t_env **env_vars, char **env);
void	add_var(t_env **env_vars, t_env *new);
t_env	*last_var(t_env *env_vars);
char	*ft_substr(const char *s, int start, int end);
int		env_cmd(t_parse	*st);
int		lstcounter(t_env	*env);
char	*ft_strjoin_env(char *s1, char *s2);
void	list2array(t_env *env, t_parse *st);
void	free_list(t_env *env);
void	empty_env(char **env, t_parse *st);
int		checking_cmd2(t_parse *st);

#endif