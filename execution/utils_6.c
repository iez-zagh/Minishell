#include "../minishell.h"

void	update(t_params *params)
{
	char	*_;

	_ = get_acc_path(params->paths_array, "env");
	search_and_replace("_", _, &(params->env), 1);
	search_and_replace("_", _, &(params->sorted_env), 1);
	update_shlvl(params);
}

void	update_shlvl(t_params *params)
{
	int			n;
	char		*lvl;

	n = ft_shell_atoi(get_key("SHLVL", params->env));
	if (n == -1)
	{
		search_and_replace("SHLVL", "1", &(params->sorted_env), 1);
		search_and_replace("SHLVL", "1", &(params->env), 1);//should allocate here
		return ;
	}
	if (n == -2)
		lvl = ft_copy("0");
	else if (++n == 999)
	{
		search_and_replace("SHLVL", "", &(params->sorted_env), 1);
		search_and_replace("SHLVL", "", &(params->env), 1);
	}
	if (n != -1 && n != -2)
		lvl = ft_shell_itoa(n);
	if (!lvl)
		return ; // more protection here
	search_and_replace("SHLVL", lvl, &(params->sorted_env), 1);
	search_and_replace("SHLVL", ft_copy(lvl), &(params->env), 1);
	
}

int	ft_shell_atoi(char *s)
{
	int	i;
	int	res;

	if (!s)
		return (-1);
	res = 0;
	i = 0;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
		{
			if (s[i + 1] >= '0' && s[i + 1] <= '9')
				return (-2);
			else
				return (-1);
		}
		else
			i++;
	}
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (-1);
		res = res * 10 + s[i] - '0';
		if (res == 100)
			return (-1);
		i++;
	}
	return (res);
}

char	*ft_shell_itoa(int n)
{
	char	*res;
	int		counter;
	int		N;

	N = n;
	counter = 0;
	while (N)
	{
		counter++;
		N = N / 10;
	}
	res = malloc (counter + 1);
	if (!res)
		return (NULL);
	res[counter] = '\0';
	counter--;
	while (counter >= 0)
	{
		res[counter] = (n % 10) + '0';
		n = n / 10;
		counter--;
	}
	return (res);
}
