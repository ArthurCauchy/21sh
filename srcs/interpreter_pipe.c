/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 11:37:10 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/26 17:12:41 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int	exec_ast_pipe(t_ast *node, int inputfd, int outputfd)
{
	int	status;
	int	pipefd[2];
	int	i;
	int	nb_children;

	if (pipe(pipefd) == -1)
		exit_error("pipe() error");
	if (g_shell.pipe_lvl == 0)
		g_shell.pipe_pgid = -1;
	g_shell.pipe_lvl += 2;
	nb_children = g_shell.pipe_lvl;
	exec_ast(node->left, inputfd, pipefd[1]);
	close(pipefd[1]); // et si je ctrl+z ?
	exec_ast(node->right, pipefd[0], outputfd);
	close(pipefd[0]);
	if (g_shell.pipe_lvl != 0)
		return (0);
	i = 0;
	while (i++ < nb_children)
		if (waitpid(-g_shell.pipe_pgid, &status, WUNTRACED) == -1)
			exit_error("waitpid() error");
	return (post_process(g_shell.pipe_pgid, status));
}
