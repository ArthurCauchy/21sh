/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_amp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 11:37:43 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/17 16:48:15 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	interpret_amp(t_ast *node, t_job **job)
{
	t_job *new_job;

	interpret(node->left, job);
	new_job = create_job();
	(*job)->is_background = 1;
	(*job)->next = new_job;
	*job = new_job;
	interpret(node->right, job);
}
