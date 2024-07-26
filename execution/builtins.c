#include "../minishell.h"

int	count_args(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
char	*ft_spliter(char *s, int j)
{
	int	i;

	i = ft_strlen(s) - 1;
	while (s[i] == '/' || s[i] == '.')
		i--;
	while(s[i] != '/')
		i--;
	return (ft_substr(s, 0, i - (j * 2)));
}

int	check_deleted(t_params *params, char *tmp2)
{
	struct stat the_path;
	char		*tmp;

	tmp = get_key("PWD", params->env);
	stat(tmp, &the_path);
	if (!S_ISDIR(the_path.st_mode))
	{
		chdir("..");
		printf("cd: error retrieving current directory: getcwd: cannot ");
		printf("access parent directories: No such file or directory\n");
		search_and_replace("OLDPWD", ft_copy(get_key("PWD", params->env)), &(params->env), 1);
		if (access(tmp2, F_OK) != -1)
			search_and_replace("PWD", tmp2, &(params->env), 1);
		else
		{
			search_and_replace("PWD", ft_strjoin2(tmp, "/.."), &(params->env), 1);
			free (tmp2);
		}
		return (1);
	}
	return (0);
}

void	no_permissions(t_params *params)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	tmp = ft_copy(get_key("PWD", params->env));
	i = ft_strlen(tmp);
	i--;
	while(tmp[i] && tmp[i] != '/')
		i--;
	tmp2 = ft_substr(tmp, 0, i);
	if (access(tmp2, X_OK) == -1)
	{
		printf("shellantics: cd: ..: Permission denied\n");
		free (tmp2);
		free (tmp);
		return ;
	}
	if (chdir(tmp2) == -1)
	{
		printf("chdir error\n");
		exit (1);
	}
	search_and_replace("OLDPWD", ft_copy(get_key("PWD", params->env)), &(params->env), 1);
	search_and_replace("PWD", tmp2, &(params->env), 1);
}

void	change_dir(t_parse *st, t_params *params, char *s)
{
	struct stat the_path;
	char		*tmp;
	static int	i = 0;

	stat(s, &the_path);
	tmp = ft_spliter(get_key("PWD", params->env), i);// handle the unset of PWD neega
	if (access(tmp, F_OK) == -1 && !(ft_strcmp("..", st->cmd[1])))
	{
		check_deleted(params, tmp);
		i++;
	}
	else if (S_ISDIR(the_path.st_mode) && access(s, X_OK) == -1) //give another try to handle the permissions
		printf("shellantics: cd: %s: Permission denied\n", s); //check the macro again
	else if (!S_ISDIR(the_path.st_mode) && access(s, F_OK) != -1)
		printf("cd: not a directory: %s\n", s);
	else if (chdir(s) == -1)
		printf("cd: no such file or directory: %s\n", s);
	else
	{
		change_pwd_value(params);
		free (tmp);
		i = 0;
	}
}
