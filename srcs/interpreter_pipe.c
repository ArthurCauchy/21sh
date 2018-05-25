/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 11:37:10 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/25 11:03:03 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int pipelvl = 0;
int pipe_last_pid = -1;

int	exec_ast_pipe(t_ast *node, int inputfd, int outputfd)
{
	int	status;
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		exit_error("pipe() error");
	pipelvl += 2;
	exec_ast(node->left, inputfd, pipefd[1]);
	close(pipefd[1]); // et si je ctrl+z ?
	exec_ast(node->right, pipefd[0], outputfd);
	close(pipefd[0]);
	waitpid(pipe_last_pid, &status, WUNTRACED);
	return (post_process(-1, status));
}
