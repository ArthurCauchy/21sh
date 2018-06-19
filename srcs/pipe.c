/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 14:31:05 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/19 15:12:00 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	add_proc_to_pipe(t_process *proc)
{
	t_process	*cur;

	cur = g_shell.pipe_processes;
	if (!cur)
		g_shell.pipe_processes = proc;
	else
	{
		while (cur->next)
			cur = cur->next;
		cur->next = proc;
	}
}

int		wait_pipe(void)
{
	t_process	*cur;
	int			status;
	int			ret;

	status = 0;
	ret = 0;
	cur = g_shell.pipe_processes;
	while (cur)
	{
		waitpid(cur->pid, &status, WUNTRACED);
		if (cur == g_shell.pipe_processes && WIFSTOPPED(status) && !g_shell.saved_processes)
			g_shell.saved_processes = copy_processes(cur);
		cur = cur->next;
	}
	if (WIFSTOPPED(status) || WIFSIGNALED(status))
	{
		ret = 1;
		g_shell.abort_command = 1;
	}
	else
		ret = WEXITSTATUS(status);
	return (ret);
}
