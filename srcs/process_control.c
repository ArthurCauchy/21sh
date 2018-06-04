/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 14:31:19 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/04 14:31:20 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

pid_t	restore_process(void)
{
	pid_t pgid;
	
	if (!g_shell.saved_processes)
		return (-1);
	pgid = g_shell.saved_processes->pid;
	tcsetpgrp(0, pgid);
	kill(-pgid, SIGCONT);
	return (pgid);
}

int		post_process(t_process *proc, int status)
{
	tcsetpgrp(0, g_shell.shell_pgid);
	if (WIFSTOPPED(status))
	{
		ft_putendl_fd("Suspended", 2);
		if (!g_shell.saved_processes)
			g_shell.saved_processes = copy_processes(proc);
		g_shell.abort_command = 1;
		return (1);
	}
	else if (WIFSIGNALED(status))
	{
		print_sig_error(WTERMSIG(status));
		g_shell.abort_command = 1;
		return (1);
	}
	return (WEXITSTATUS(status));
}
