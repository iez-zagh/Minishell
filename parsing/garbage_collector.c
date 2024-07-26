#include "../minishell.h"

void	garbage_collector(t_garbage **gr, void	*p)
{
	t_garbage	*tmp;
	t_garbage	*new_g;

	new_g = malloc(sizeof(t_garbage));
	new_g->next = NULL;
	new_g->p = p;
	if (!*gr)
		*gr = new_g;
	else
	{
		tmp = *gr;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_g;
	}
}

void	empty_garbage(t_garbage **gr)
{
	t_garbage	*tmp;

	while (*gr)
	{
		tmp = *gr;
		*gr = (*gr)->next;
		free(tmp->p);
		free(tmp);
	}
}

void	*ft_malloc(size_t size, int flag)
{
	void				*p;
	static t_garbage	*gr;

	if (flag == 1 || flag == 0)
	{
		p = malloc(size);
		if (!p)
			return (NULL);
		else
			if (flag)
				garbage_collector(&gr, p);
		return (p);
	}
	else
		empty_garbage(&gr);
	return (NULL);
}
