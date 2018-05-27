#include "twenty_one_sh.h"

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
