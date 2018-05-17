/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 11:16:48 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/17 16:15:13 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	interpret(t_ast *node, t_job **job)
{
	if (node->token == AMP)
		interpret_amp(node, job);
	else if (node->token == SEMICOL)
		interpret_semicol(node, job);
	else if (node->token == OR)
		interpret_or(node, job);
	else if (node->token == AND)
		interpret_and(node, job);
	else if (node->token == PIPE)
		interpret_pipe(node, job);
	else
		interpret_arg(node, job);
}
