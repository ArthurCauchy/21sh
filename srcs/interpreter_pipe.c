/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 11:37:10 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/26 14:23:53 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int	exec_ast_pipe(t_ast *node, int *pipein, int *pipeout)
{
	int	pipefd[2];
	int	ret;

	if (pipe(pipefd) == -1)
		exit_error("pipe() error");
	if (g_shell.pipe_lvl == 0)
	{
		g_shell.pipe_pgid = -1;
		g_shell.pipe_lvl = 1;
	}
	g_shell.pipe_lvl += 1;
	exec_ast(node->left, pipein, pipefd);
	close(pipefd[1]);
	exec_ast(node->right, pipefd, pipeout);
	close(pipefd[0]);
	if (g_shell.pipe_lvl != 0)
		return (0);
	ret = wait_pipe();
	g_shell.pipe_pgid = -1;
	delete_processes(g_shell.pipe_processes);
	g_shell.pipe_processes = NULL;
	tcsetpgrp(0, g_shell.shell_pgid);
	return (ret);
}
