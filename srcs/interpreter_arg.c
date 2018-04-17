/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 11:37:02 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/17 14:09:15 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void	delete_args(char **args)
{
	size_t  i;
	
	i = 0;
	while (args[i])
	{
		free(args[i]);
		++i;
	}
	free(args);
}

static void	analyze_arglist(t_word *arglist, char **args)
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

int			exec_ast_arg(t_ast *node, int inputfd, int outputfd)
{
	char	**args;
	int		ret;

	if (!(args = (char**)malloc((PARAMS_MAX + 1) * sizeof(char*))))
		exit_error("malloc() error");
	analyze_arglist(node->arglist, args);
	ret = start_command(g_envptr, g_envptr, args, inputfd, outputfd);
	delete_args(args);
	return (ret);
}
