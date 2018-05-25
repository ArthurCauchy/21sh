#include "twenty_one_sh.h"

pid_t	g_saved_pid = -1;

pid_t	restore_process(void)
{
	pid_t pid;
	if (g_saved_pid != -1)
	{
		kill(g_saved_pid, SIGCONT);
		pid = g_saved_pid;
		g_saved_pid = -1;
		return (pid);
	}
	return (-1);
}

int		post_process(pid_t pid, int status)
{
	if (pid > 0 && WIFSTOPPED(status))
	{
		ft_putendl_fd("Suspended", 2);
		g_saved_pid = pid;
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
