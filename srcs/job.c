/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 11:37:20 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/17 15:29:50 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

t_job	*create_job(void)
{
	t_job	*new;

	new = (t_job*)malloc(sizeof(t_job));
	new->next = NULL;
	new->first_process = NULL;
	new->pgid = -1;
	new->is_background = 0;
	return (new);
}

void	delete_job(t_job *job)
{
	t_process	*prev;
	t_process	*cur;

	prev = NULL;
	cur = job->first_process;
	while (cur)
	{
		prev = cur;
		cur = cur->next;
		delete_process(prev);
	}
	free(job->command);
	free(job);
}
