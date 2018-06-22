/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 14:27:33 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/22 15:52:18 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int	builtin_fg(t_env **env, char **args)
{
	t_process	*tmp_proc;
	pid_t		pid;
	int			status;
	int			ret;

	(void)env;
	if (args[1])
	{
		ft_putendl_fd("fg: Too many arguments.", 2);
		return (1);
	}
	if ((pid = restore_process()) == -1)
	{
		ft_putendl_fd("No stopped process.", 2);
		return (1);
	}
	tmp_proc = copy_processes(g_shell.saved_processes);
	delete_processes(g_shell.saved_processes);
	g_shell.saved_processes = NULL;
	if (tmp_proc->next)
	{
		g_shell.pipe_pgid = tmp_proc->pid;
		g_shell.pipe_processes = tmp_proc;
		ret = wait_pipe();
		g_shell.pipe_pgid = -1;
		delete_processes(g_shell.pipe_processes);
		g_shell.pipe_processes = NULL;
		tcsetpgrp(0, g_shell.shell_pgid);
		return (ret);
	}
	if (waitpid(pid, &status, WUNTRACED) == -1)
		exit_error("waitpid() error");
	ret = post_process(tmp_proc, status);
	delete_processes(tmp_proc);
	tcsetpgrp(0, g_shell.shell_pgid);
	return (ret);
}
