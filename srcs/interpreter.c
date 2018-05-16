/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 11:16:48 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/16 14:30:05 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	interpret(t_ast *node)
{
	if (node->token == AMP)
		return (interpret_amp(node));
	if (node->token == SEMICOL)
		return (interpret_semicol(node));
	else if (node->token == OR)
		return (interpret_or(node));
	else if (node->token == AND)
		return (interpret_and(node));
	else if (node->token == PIPE)
		return (interpret_pipe(node));
	else
		return (interpret_arg(node));
}
