#include "../minishell.h"

void	print(t_parse *parse)
{
	int	i;

	t_parse *tmp = parse;
	while (tmp)
	{
		i = 0;
		printf("-------cmd------\n");
		while ((tmp)->cmd[i])
		{
			printf("%s\n", (tmp)->cmd[i]);
			i++;
		}
		i = 0;
		printf("-------files-------\n");
		t_files *tmp2 = tmp->files;
		while (tmp2)
		{
			printf("%s -> %d | amb: %d\n", tmp2->file, tmp2->type, tmp2->is_amb);
			tmp2 = tmp2->next;
		}
		printf("---------in_dup------\n");
		if ((tmp)->in_dup)
			printf("%s\n", (tmp)->in_dup);
		printf("---------out_dup------\n");
		if ((tmp)->out_dup)
			printf("%s\n", (tmp)->out_dup);
		(tmp) = (tmp)->next;
		if ((tmp))
		printf("**********next********\n");
	}
}