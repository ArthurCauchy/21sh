/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 09:42:57 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/01 17:56:03 by arthur           ###   ########.fr       */
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
	t_process   *new;
	char		**new_args;

	if (!src)
		return (NULL);
	if (!(new = (t_process*)malloc(sizeof(t_process))))
		exit_error("malloc() error");
	new_args = (char**)malloc(sizeof(char*) * 2); // bidouillage pour garder juste le nom en fait
	new_args[0] = ft_strdup(src->args[0]);
	new_args[1] = NULL;
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
