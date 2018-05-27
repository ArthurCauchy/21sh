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
		// set a global to prevent further exec
		return (1);
	}
	else if (WIFSIGNALED(status))
	{
		print_sig_error(WTERMSIG(status));
		// set a global to prevent further exec
		return (1);
	}
	return (WEXITSTATUS(status));
}
