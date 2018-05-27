/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 09:42:57 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/27 15:06:27 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

t_process	*new_process(void)
{
	t_process	*new;

	if (!(new = (t_process*)malloc(sizeof(t_process))))
		exit_error("malloc() error");
	new->next = NULL;
	new->path = NULL;
	new->args = NULL;
	new->redirs = NULL;
	return (new);
}

void		delete_processes(t_process *procs)
{
	t_process	*prev;
	t_process	*cur;

	prev = NULL;
	cur = procs;
	while (cur)
	{
		prev = cur;
		cur = cur->next;
		// free and delete
		free(prev);
	}
}
