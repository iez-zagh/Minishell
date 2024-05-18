#include "minishell.h"

int	count_args(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	change_dir(t_parse *st, char *s)
{
	struct stat the_path;

	stat(s, &the_path);
	if (!S_ISDIR(the_path.st_mode) && access(s, F_OK) != -1)
	{
			printf("cd: not a directory: %s\n", s);
			return ;
	}
	if (chdir(s) == -1)
	{
		printf("cd: no such file or directory: %s\n", s);	
		return ;
	}
	else
		change_pwd_value(st);
}