/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 09:42:57 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/25 12:03:19 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int			g_running_proc = -1;

extern int pipelvl;
extern pid_t pipe_last_pid;

int			start_process(t_env **env, char **args)
{
	pid_t	pid;
	int		status;
	int		ret;

	pid = fork();
	if (pid == -1)
		exit_error("fork() error");
	if (pid == 0)
	{
		reset_sighandlers();
		if (execve(args[0], args, env_to_array(env)))
			exit_error("execve() error");
	}
	else
	{
		if (pipelvl == 0)
		{
			pipe_last_pid = pid;
			g_running_proc = pid;
			if (waitpid(pid, &status, WUNTRACED) == -1)
				exit_error("waitpid() error");
			g_running_proc = -1;
			ret = post_process(pid, status);
			return (ret);
		}
		else
			--pipelvl;
	}
	return (0);
}
