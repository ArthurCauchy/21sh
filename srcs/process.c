/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 09:42:57 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/25 16:07:11 by acauchy          ###   ########.fr       */
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
	new->pid = -1;
	return (new);
}

t_process	*copy_processes(t_process *src)
{
	t_process	*new;
	char		**new_args;

	if (!src)
		return (NULL);
	if (!(new = (t_process*)malloc(sizeof(t_process))))
		exit_error("malloc() error");
	new_args = copy_args(src->args);
	if (src->path)
		new->path = ft_strdup(src->path);
	else
		new->path = NULL;
	new->args = new_args;
	new->redirs = NULL;
	new->pid = src->pid;
	new->next = copy_processes(src->next);
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
		free(prev->path);
		delete_args(prev->args);
		delete_redirects(prev->redirs);
		free(prev);
	}
}
