/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 11:37:02 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/15 15:06:03 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

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

int			exec_ast_arg(t_ast *node, int is_piped)
{
	char		*errmsg;
	char		**args;
	t_process	*proc;
	t_job		*job;

	args = (char**)malloc((PARAMS_MAX + 1) * sizeof(char*));
	analyze_arglist(node->arglist, &args);
	proc = create_process(&args);
	if (is_piped)
	{
		job = job->next;

		(0);
	}
	return (start_job(g_envptr, ));
}
