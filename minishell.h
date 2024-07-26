/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ../minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:50:47 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/06/03 17:10:55 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <dirent.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <stdbool.h>

# define RED_TEXT "\033[1;31m"
# define GREEN_TEXT "\033[1;32m"
# define YELLOW_TEXT "\033[1;33"
# define RESET_TEXT "\033[0m"
# define BLUE_TEXT "\033[1;34m"


typedef	struct	t_env
{
	// name=hamza
	char		*key; // $name
	char		*value; // hamza
	struct t_env *next;
}		t_env;

typedef	struct	t_count
{
	int in;
	int out;
	int app;
	int words;
}   t_count;

typedef	struct t_token
{
	char			*value;
	char			*type;
	int 			flag;
	int 			wh;
	int 			here;
	int 			has_q;
	int 			status;
	t_env			*env;
	struct t_token	*next;
}	t_token;

typedef struct t_garbage
{
    void    *p;
    struct t_garbage *next;
}   t_garbage;

typedef struct t_decl
{
	int still;
	int first;
	int j;
	int i;
	char    *value;
	t_env	*env;
}   t_decl;

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
	char 	*line;
	int		fd;
	int		i;
	int		f_time;
}	t_decl3;

typedef struct t_files
{
	char	*file;
	int		type;
	int		is_amb;
	struct t_files *next;
}	t_files;

typedef struct t_params
{
	int				flag; //remove this later
	int				flag_2;
	int				cmds;
	char			**paths_array;
	char			*path;
	char			**env2;
	char			**env3;
	t_env			*sorted_env;
	t_env			*env;
	int				export_f;
	int				q;
	int				status;
	char			*line;
	int				save_fd;
	int				i;
	int				fds[2];
	int				pid;
}   t_params;

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
	struct t_parse *next;
}		t_parse;

// parsing

char	*ft_strdup(const char *s1);
void     tokenize(t_token **token, char *line, int *q);
char	**ft_mysplit(char const *s, char c, int *still);
void	add_back(t_token **token, t_token *new);
void	exit_syntax_error(char *error_msg);
char	*ft_mysubstr(char const *s, unsigned int start, size_t len);
int		is_in_word(char c);
int		is_white(char c);
int		is_alph_num(char c);
char	*ft_strjoin(char *s1, char *s2);
int 	syntax(t_token *token);
void	tokens_reset(t_token **token);
void	expander(t_token *token, t_params params);
int	    in_str(char *str, char c);
void	quotes_removal(t_token *tokens);
int	    is_alph(char c);
void    parser(t_token *tokens, t_parse **parse, t_params *params);
void	add_back_parse(t_parse **parse, t_parse *new);
void	non_quotes_expander(t_token **token, t_params params);
void	add_middle(t_token **token, char **arr);
int	    word_count(char *str);
int	    white_word(char *str);
void	add_middle_n(t_token **token, char *value);
int	    no_rest(char *str, int i);
void	quotes_expander(t_token **token, char *token_value, t_params params);
void	comp(t_decl decl, t_token **token, char *token_value, int *i);
void	out_quotes(t_decl2 *decl, char *t_v, t_token **token, t_params params);
void	first_word_pos(char *value, int *i, int *j);
char	*ft_itoa(int n);
void	expand_line(char **line, t_params *params);
void	*ft_malloc(size_t size, int flag);
void 	parse_input(t_token **tokens, t_parse **new_parse);
void	parse_output(t_token **tokens, t_parse **new_parse);
void	parse_append(t_token **tokens, t_parse **new_parse);
void	parse_heredoc(t_decl3 *decl, t_token **tokens, t_parse **new_parse, t_params *params);
void	is_in_quote(t_decl2 *decl, char *t_v);
void	add_back_file(t_files **files, int type, t_token *token, t_parse *parse);
void	not_w_first_i(t_decl *decl, char **n_t_v, t_token **token);
void	print(t_parse *parse);

// execution

void	wait_prompt1(t_params *params);
void	signal_handle(void);
char	*get_acc_path(char **paths, char *com);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
void	error(t_parse *st, int y, t_params *params);
void	free_array(char **array);
char	**ft_split(char const *s, char c);
void	excute_cmd(t_parse *st, t_params *params);
void	ft_free(char **s);
void	change_directory(t_parse *st, t_params *params);
void	terminate_shell(t_parse *st, t_params *params);
int		ft_strcmp(char *s1, char *s2);
int		count_args(char **s);
int		numbered_arg(char *s);
void	freeing(t_parse *st, t_params *params);
size_t	ft_atol(char *s, t_parse *st, t_params *params);
void	ft_exit(t_parse *st, int args_n, t_params *params);
int		checking_cmd(t_parse *st, t_params *params);
t_env	*set_env(char **env);
void	add_var(t_env **env_vars, t_env *new);
t_env	*last_var(t_env *env_vars);
char	*ft_substr(const char *s, int start, int end);
int		env_cmd(t_parse	*st, t_params *params);
int		lstcounter(t_env	*env);
char	*ft_strjoin_env(char *s1, char *s2);
char	**list2array(t_env *env, t_params *params);
void	free_list(t_env *env);
void	empty_env(t_params *params);
int		checking_cmd2(t_parse *st, t_params *params);
char	*get_key(char *s, t_env *env);
char	*ft_copy(const char *s);
void	export_cmd(char **s, char *res, t_params *params);
void	add_key(char *key, char *value, t_env **env);
void	search_and_replace(char *env, char *value, t_env **envi, int flag);
char	*get_pwd(t_params *params);
void	change_pwd_value(t_params *params);
t_env	*before_last_node(t_env *env);
void	ft_free2(t_parse *st);
void	freeing2(t_parse *st);
void	change_dir(t_parse *st, t_params *params, char *s);
void	sort_env(t_env *env);
void	just_export(t_params *params);
void	ft_swap(t_env *a, t_env *b);
void	check_join(char **s, t_parse *st, t_params *params);
void	ft_join_value(char **s, t_parse *st, t_params *params);
void	ft_join(char **res, t_params *params);
void	export_cmd1(t_parse *st, t_params *params);
int 	ft_strchr(char *s, char c);
int		search_and_replace2(char *env, t_env **envi);
void	free_update(char **res, t_params *params);
char	**export_checker(char *s);
int		check_syntax(char *s);
char	**copy_env(char **env);
void	pwd_cmd(t_params *params);
void	unset_cmd(t_parse *st, t_params *params);
void	unset_cmd1(t_env **env, char *s);
int		checking_cmd3(t_parse *st, t_params *params);
void	update(t_params *params);
int		ft_shell_atoi(char *s);
void	update_shlvl(t_params *params);
char	*ft_shell_itoa(int n);
char	**export_checker2(char **res, char *s, int i);
char	*ft_strjoin2(char *s1, char *s2);
char	*ft_strdup2(const char *s1);
int		back_cmd(t_parse *st, int it, t_params *params);
int		in_out_dup(t_parse *st, t_params *params);
void	slash_path(t_parse *st, t_params *params);
int		lstsize(t_parse	*env);
int		first_cmd(int fds[2]);
int 	last_cmd(int fds[2]);
void	update_(t_parse *st, t_params *params);
int		check_builtins(char *s);
void	forking_checker(t_parse *st, t_params *params, int i);
void	initialiaze_vars(t_params *params, int *i, t_token **token, int f);

#endif
