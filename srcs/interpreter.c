/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 11:16:48 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/04 09:02:51 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int	exec_ast(t_ast *node, int *pipein, int *pipeout)
{
	if (g_shell.abort_command == 1)
		return (1);
	if (node->token == SEMICOL)
		return (exec_ast_semicol(node, pipein, pipeout));
	else if (node->token == OR)
		return (exec_ast_or(node, pipein, pipeout));
	else if (node->token == AND)
		return (exec_ast_and(node, pipein, pipeout));
	else if (node->token == PIPE)
		return (exec_ast_pipe(node, pipein, pipeout));
	else
		return (exec_ast_arg(node, pipein, pipeout));
}
