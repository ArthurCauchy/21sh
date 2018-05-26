#include "twenty_one_sh.h"

pid_t	restore_process(void)
{
	pid_t pgid;
	
	pgid = g_shell.saved_pgid;
	if (pgid != -1)
	{
		tcsetpgrp(0, pgid);
		kill(-pgid, SIGCONT);
		g_shell.saved_pgid = -1;
		return (pgid);
	}
	return (-1);
}

int		post_process(pid_t pid, int status)
{
	tcsetpgrp(0, g_shell.shell_pgid);
	if (pid > 0 && WIFSTOPPED(status))
	{
		ft_putendl_fd("Suspended", 2);
		g_shell.saved_pgid = getpgid(pid);
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
