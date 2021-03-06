/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starter_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 09:42:57 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/26 17:28:35 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void	start_forked(t_env **env, t_process *proc, char **errmsg)
{
	pid_t	pid;

	pid = getpid();
	if (g_shell.pipe_lvl == 0 || g_shell.pipe_processes == NULL)
	{
		setpgid(pid, pid);
		tcsetpgrp(0, pid);
	}
	else
		setpgid(pid, g_shell.pipe_pgid);
	reset_sighandlers();
	if (apply_redirects(proc->redirs, NULL, NULL, errmsg) == -1)
		exit_error(*errmsg);
	execve(proc->path, proc->args, env_to_array(env));
	exit_error("execve() error");
}

static int	father_register_child(t_process *proc, pid_t pid)
{
	int	status;

	proc->pid = pid;
	if (g_shell.pipe_lvl == 0)
	{
		tcsetpgrp(0, pid);
		if (waitpid(pid, &status, WUNTRACED) == -1)
			exit_error("waitpid() error");
		return (post_process(proc, status));
	}
	else
	{
		if (!g_shell.pipe_processes)
		{
			tcsetpgrp(0, pid);
			g_shell.pipe_pgid = pid;
		}
		add_proc_to_pipe(copy_processes(proc));
	}
	return (0);
}

int			start_process(t_env **env, t_process *proc)
{
	int		ret;
	pid_t	pid;
	char	*errmsg;

	ret = 0;
	errmsg = NULL;
	if ((pid = fork()) < 0)
		exit_error("fork() error");
	else if (pid == 0)
		start_forked(env, proc, &errmsg);
	else
		ret = father_register_child(proc, pid);
	return (ret);
}
