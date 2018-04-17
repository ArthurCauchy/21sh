/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 09:42:57 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/17 14:07:16 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int			g_running_proc = -1;

static int	post_process(int status)
{
	if (WIFSIGNALED(status))
	{
		print_sig_error(WTERMSIG(status));
		return (1);
	}
	return (WEXITSTATUS(status));
}

static void	replace_fd(int to_close, int to_dup)
{
	close(to_close);
	dup(to_dup);
}

int			start_process(t_env **env, char **args, int inputfd, int outputfd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		exit_error("fork() error");
	if (pid == 0)
	{
		if (inputfd != 0)
			replace_fd(0, inputfd);
		if (outputfd != 1)
			replace_fd(1, outputfd);
		if (execve(args[0], args, env_to_array(env)))
			exit_error("execve() error");
	}
	else
	{
		g_running_proc = pid;
		wait(&status);
		if (status == -1)
			exit_error("wait() error");
		g_running_proc = -1;
		return (post_process(status));
	}
	return (0);
}
