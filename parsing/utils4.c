#include "../minishell.h"

int	word_count(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
		i++;
		if (str[i])
			count ++;
		while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			i++;
		}
	return count;
}

int	white_word(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	no_rest(char *str, int i)
{
	while (str[i])
	{
		if (!is_white(str[i]))
			return (0);
		i++;
	}
	return (1);
}