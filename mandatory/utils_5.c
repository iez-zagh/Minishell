#include "minishell.h"

int	check_syntax(char *s)
{
	int	i;

	i = 0;
	if (!((s[i] >= 'a' && s[i] <= 'z')
		|| (s[i] >= 'A' && s[i] <= 'Z') || (s[i] == '_')))
		return (1);
	// while (s[i])
	// {

	// }
	return (0);
}
 