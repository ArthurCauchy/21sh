/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 11:37:20 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/23 12:43:21 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

t_job	*create_job(void)
{
	t_job	*new;

	new = (t_job*)malloc(sizeof(t_job));
	new->next = NULL;
	new->arg_tree = NULL;
	new->proc_list = NULL;
	new->pgid = -1;
	new->is_background = 0;
	return (new);
}

void	delete_job(t_job *job)
{
	delete_ast(&job->arg_tree);
	free(job);
}
