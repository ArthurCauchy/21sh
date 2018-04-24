/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 14:24:18 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/24 14:03:46 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static t_builtin	**get_builtins(void)
{
	static t_builtin	*builtins[BUILTIN_MAX] = {NULL};

	return (builtins);
}

/*
** Clear the loaded builtins.
** Has to be performed before exiting to avoir memory leaks.
*/

void				clear_builtins(void)
{
	t_builtin	**builtins;
	int			i;

	builtins = get_builtins();
	i = 0;
	while (i < BUILTIN_MAX && builtins[i] != NULL)
	{
		free(builtins[i]);
		++i;
	}
}

/*
** Loads a new builtin command.
*/

void				load_builtin(char *name, int (*func)(t_env**, char**))
{
	t_builtin	*new;
	t_builtin	**builtins;
	int			i;

	if (!(new = (t_builtin*)ft_memalloc(sizeof(t_builtin))))
		exit_error("load_builtin malloc() error");
	new->name = name;
	new->func = func;
	builtins = get_builtins();
	i = 0;
	while (i < BUILTIN_MAX && builtins[i] != NULL)
		++i;
	builtins[i] = new;
}

/*
** Search a builtin correspunding to 'input' param and execute
** the correspunding function.
**
** Returns :
** 0 = ok
** -1 = error with the builtin
** -2 = not a builtin
*/

int					search_start_builtin(t_env **env, char **args)
{
	t_builtin	**builtins;
	int			i;

	builtins = get_builtins();
	i = 0;
	while (i < BUILTIN_MAX && builtins[i] != NULL)
	{
		if (ft_strcmp(args[0], builtins[i]->name) == 0)
		{
			return (builtins[i]->func(env, args));
		}
		++i;
	}
	return (-2);
}
