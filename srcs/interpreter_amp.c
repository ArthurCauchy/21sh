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

void	interpret_amp(t_ast *node, t_job **job, int bg)
{
	t_job *new_job;

	(*job)->arg_tree = copy_ast(node->left);
	interpret(node->left, job, 1);
	new_job = create_job();
	new_job->is_background = bg;
	(*job)->next = new_job;
	*job = new_job;
	interpret(node->right, job, bg);
}
