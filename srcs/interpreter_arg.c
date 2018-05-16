/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 11:37:02 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/16 15:07:25 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

/*static void	analyze_arglist(t_word *arglist, char **args)
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
}*/

void	interpret_arg(t_ast *node, t_job *job)
{
	t_process	*proc;
	t_process	*cur;

	proc = create_process(node->arglist);
	cur = job->first_process;
	while (cur)
		cur = cur->next;
	if (cur)
		cur->next = proc;
	else
		job->first_process = proc;
}
