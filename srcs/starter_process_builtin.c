/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starter_process_builtin.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 12:03:19 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/26 17:28:32 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	start_forked(t_env **env, t_process *proc, t_builtin_fct builtin)
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
	exit(builtin(env, proc->args));
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

int			fork_start_builtin(t_env **env,
		t_process *proc, t_builtin_fct builtin)
{
	int		ret;
	pid_t	pid;

	ret = 0;
	if ((pid = fork()) < 0)
		exit_error("fork() error");
	else if (pid == 0)
		ret = start_forked(env, proc, builtin);
	else
		ret = father_register_child(proc, pid);
	return (ret);
}
