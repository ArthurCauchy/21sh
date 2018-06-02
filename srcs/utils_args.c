#include "twenty_one_sh.h"

void	analyze_arglist(t_word *arglist, char **args)
{
	t_word	*cur;
	size_t	i;

	cur = arglist;
	i = 0;
	while (i < PARAMS_MAX && cur)
	{
		args[i] = ft_strdup(cur->str);
		++i;
		cur = cur->next;
	}
	args[i] = NULL;
}

char	**copy_args(char **args)
{
	char	**new;
	int		i;

	new = ft_memalloc(sizeof(char*) * PARAMS_MAX);
	i = 0;
	while (args[i])
	{
		new[i] = ft_strdup(args[i]);
		++i;
	}
	return (new);
}

void	delete_args(char **args)
{
	size_t	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		++i;
	}
	free(args);
}
