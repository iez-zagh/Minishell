#include "../minishell.h"

int	is_alph_num(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >='A' && c <= 'Z') || (c >= '0' && c <= '9'));
}

int	is_alph(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >='A' && c <= 'Z'));
}

int	is_white(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

int	is_special(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	is_in_word(char c)
{
	if (is_alph_num(c) || (!is_white(c) && !is_special(c)))
		return (1);
	return (0);
}