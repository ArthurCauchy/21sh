/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 11:37:02 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/23 13:19:00 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void	analyze_arglist(t_word *arglist, char **args)
{
	t_word	*cur;
	size_t	i;

	cur = arglist;
	i = 0;
	while (i < PARAMS_MAX - 1 && cur)
	{
		args[i] = ft_strdup(cur->str);
		++i;
		cur = cur->next;
	}
	args[i] = NULL;
}

void	interpret_arg(t_ast *node, t_job *job)
{
	char		**args;
	t_process	*proc;
	t_process	*tmp;

	args = malloc(sizeof(char*) * PARAMS_MAX);
	analyze_arglist(node->arglist, args);
	proc = create_process(&args);
	if (!job->proc_list)
		job->proc_list = proc;
	else
	{
		tmp = job->proc_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = proc;
	}
	start_process(g_envptr, job, proc);
}
