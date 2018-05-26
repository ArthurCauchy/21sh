/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 09:42:57 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/26 16:29:59 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int			start_process(t_env **env, char **args)
{
	pid_t	pid;
	int		status;
	int		ret;

	if ((pid = fork()) < 0)
		exit_error("fork() error");
	else if (pid == 0)
	{
		pid = getpid();
		if (g_shell.pipe_lvl == 0 || g_shell.pipe_pgid == -1)	
		{
			setpgid(pid, pid);
			tcsetpgrp(0, pid);
		}
		else
			setpgid(pid, g_shell.pipe_pgid);
		reset_sighandlers();
		if (execve(args[0], args, env_to_array(env)))
			exit_error("execve() error");
	}
	else
	{
		if (g_shell.pipe_lvl == 0)
		{
			tcsetpgrp(0, pid);
			if (waitpid(pid, &status, WUNTRACED) == -1)
				exit_error("waitpid() error");
			ret = post_process(pid, status);
			return (ret);
		}
		else
		{
			if (g_shell.pipe_pgid == -1)
			{
				g_shell.pipe_pgid = pid;
				tcsetpgrp(0, pid);
			}
			--g_shell.pipe_lvl;
		}
	}
	return (0);
}
