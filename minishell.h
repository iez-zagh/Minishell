/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0024/04/19 10:50:47 by ez-zagh           #+#    #+#             */
/*   Updated: 2024/08/07 18:54:57 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>

# define RED_TEXT "\033[1;31m"
# define GREEN_TEXT "\033[1;32m"
# define YELLOW_TEXT "\033[1;33"
# define RESET_TEXT "\033[0m"
# define BLUE_TEXT "\033[1;34m"

int		g_status;

typedef struct t_env
{
	char			*key;
	char			*value;
	struct t_env	*next;
}		t_env;

typedef struct t_count
{
	int	in;
	int	out;
	int	app;
	int	words;
}	t_count;

typedef struct t_token
{
	char			*value;
	char			*type;
	int				flag;
	int				wh;
	int				here;
	int				has_q;
	t_env			*env;
	int				status;
	struct t_token	*next;
}	t_token;

typedef struct t_garbage
{
	void				*p;
	struct t_garbage	*next;
}	t_garbage;

typedef struct t_decl
{
	int		still;
	int		first;
	int		j;
	int		i;
	char	*value;
	t_env	*env;
}	t_decl;

typedef struct t_decl2
{
	int		in_quote;
	int		i;
	char	quote;
	char	*n_t_v;
	int		start;
	char	*value;
	int		j;
	int		z;
	int		h;
	int		still;
}	t_decl2;

typedef struct t_decl3
{
	int		l;
	char	*line;
	int		fd;
	int		save_fd;
	int		i;
}	t_decl3;

typedef struct t_files
{
	char			*file;
	int				type;
	int				is_amb;
	struct t_files	*next;
}	t_files;

typedef struct t_params
{
	int		flag; //remove this later
	int		flag_2;
	int		cmds;
	char	**paths_array;
	char	*path;
	char	**env2;
	char	**env3;
	t_env	*sorted_env;
	t_env	*env;
	int		export_f;
	int		q;
	char	*line;
	int		save_fd;
	int		i;
	int		fds[2];
	int		pid;
	int		stdin_;
	int		stdout_;
	int		status;
	int		path_flag;
}	t_params;

typedef struct t_parse
{
	char			*com_path;
	char			**cmd;
	t_files			*files;
	char			*in_dup;
	char			*out_dup;
	int				in_fd;
	int				out_fd;
	int				i;
	struct t_parse	*next;
}	t_parse;

// parsing

void	signal_pro(t_decl3 *decl, t_params *params);
int		fork_failure(t_params *params);
void	malloc_error(t_params *params);
int		minishell(t_parse *st);
char	*ft_strdup(const char *s1);
void	tokenize(t_token **token, char *line, t_params *params);
char	**ft_mysplit(char const *s, char c, int *still);
void	add_back(t_token **token, t_token *new);
void	syntax_error(char *error_msg, t_params *params);
char	*fmysubstr(char const *s, unsigned int start, size_t len);
int		is_in_word(char c);
int		is_white(char c);
int		is_alph_num(char c);
char	*ft_strjoin(char *s1, char *s2);
int		syntax(t_token *token, t_params *params);
void	expander(t_token *token, t_params params);
int		in_str(char *str, char c);
void	quotes_removal(t_token *tokens);
int		is_alph(char c);
int		parser(t_token *tokens, t_parse **parse, t_params *params);
void	add_back_parse(t_parse **parse, t_parse *new);
void	non_quotes_expander(t_token **token, t_params params);
void	add_middle(t_token **token, char **arr);
int		word_count(char *str);
int		white_word(char *str);
void	add_middle_n(t_token **token, char *value);
int		no_rest(char *str, int i);
void	quotes_expander(t_token **token, char *token_value, t_params params);
void	comp(t_decl decl, t_token **token, char *token_value, int *i);
void	out_quotes(t_decl2 *decl, char *t_v, t_token **token, t_params params);
void	first_word_pos(char *value, int *i, int *j);
char	*ft_itoa(int n);
void	expand_line(char **line, t_params *params);
void	*ft_malloc(size_t size, int flag);
void	parse_input(t_token **tokens, t_parse **new_parse);
void	parse_output(t_token **tokens, t_parse **new_parse);
void	parse_append(t_token **tokens, t_parse **new_parse);
int		doc(t_decl3 *decl, t_token **tokens,
			t_parse **new_parse, t_params *params);
void	is_in_quote(t_decl2 *decl, char *t_v);
void	add_back_file(t_files **files,
			int type, t_token *token, t_parse *parse);
void	not_w_first_i(t_decl *decl, char **n_t_v, t_token **token);
void	heredoc_sig(int sig);
int		pipe_syntax(t_token *token, t_params *params);
int		redirection_syntax(t_token *token, t_params *params);
int		echo_cmd(t_parse *st);
int		ft_shell_atoi(char *s);
void	change_pwd(t_params *params, char *tmp, int *i);
int		just_echo(t_parse *st);
char	*set_status(int status);

// execution

void	wait_prompt1(t_params *params);
void	signal_handle(void);
char	*get_acc_path(char **paths, char *com);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
void	free_array(char **array);
char	**ft_split(char const *s, char c);
void	excute_cmd(t_parse *st, t_params *params);
void	ft_free(char **s);
int		change_directory(t_parse *st, t_params *params);
int		terminate_shell(t_parse *st, t_params *params);
int		ft_strcmp(char *s1, char *s2);
int		count_args(char **s);
int		numbered_arg(char *s);
void	freeing(t_params *params);
size_t	ft_atol(char *s, t_params *params);
void	ft_exit(t_parse *st, int args_n, t_params *params);
int		checking_cmd(t_parse *st, t_params *params);
t_env	*set_env(char **env, int i);
void	add_var(t_env **env_vars, t_env *new);
t_env	*last_var(t_env *env_vars);
char	*ft_substr(const char *s, int start, int end);
int		env_cmd(t_parse	*st, t_params *params);
int		lstcounter(t_env *env);
char	*ft_strjoin_env(char *s1, char *s2, t_params *params);
char	**list2array(t_env *env, t_params *params);
void	free_list(t_env *env);
void	empty_env(t_params *params);
char	*get_key(char *s, t_env *env);
char	*ft_copy(const char *s);
void	export_cmd(char **s, char *res, t_params *params);
void	search_and_replace(char *env, char *value, t_env **envi, int flag);
char	*get_pwd(t_params *params);
void	change_pwd_value(t_params *params);
t_env	*before_last_node(t_env *env);
int		change_dir(t_parse *st, t_params *params, char *s);
void	sort_env(t_env *env);
void	check_join(char **s, t_parse *st, t_params *params);
void	ft_join(char **res, t_params *params);
int		export_cmd1(t_parse *st, t_params *params);
int		ft_strchr(char *s, char c);
int		search_and_replace2(char *env, t_env **envi);
void	free_update(char **res, t_params *params);
char	**export_checker(char *s, t_params *params);
int		check_syntax(char *s);
char	**copy_env(char **env);
int		pwd_cmd(t_params *params);
int		unset_cmd(t_parse *st, t_params *params);
void	unset_cmd1(t_env **env, char *s);
int		checking_cmd3(t_parse *st, t_params *params);
void	update(t_params *params);
char	**export_checker2(char **res, char *s, int i);
char	*ft_strjoin2(char *s1, char *s2);
char	*ft_strdup2(const char *s1);
int		in_out_dup(t_parse *st, t_params *params);
void	slash_path(t_parse *st, t_params *params);
int		lstsize(t_parse	*env);
void	update_(t_parse *st, t_params *params);
int		check_builtins(char *s);
void	forking_checker(t_parse *st, t_params *params);
void	initialiaze_vars(t_params *params, t_token **token, int f);
void	excute_cmds(t_parse *st, t_params *params);
void	forking_piping(t_params *params);
void	print_error(char *cmd, char *s, char *folder);
void	checking_and_exec(t_parse *st, t_params *params);
int		just_a_checker(t_parse *st, t_params *params);
char	*ft_slashs(t_parse *st);
int		open_fs(t_parse *st, int out);

#endif
