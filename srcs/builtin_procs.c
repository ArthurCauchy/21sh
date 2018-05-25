#include "twenty_one_sh.h"

extern pid_t g_saved_pid;

int	builtin_procs(t_env **env, char **args)
{
	(void)env;
	if (args[1])
	{
		ft_putendl_fd("procs: Too many arguments.", 2);
		return (1);
	}
	// save le nom du process (entre autres) ca serait cool
	if (g_saved_pid == -1)
	{
		ft_putendl_fd("No stopped process.", 2);
		return (1);
	}
	ft_putnbr(g_saved_pid);
	ft_putchar('\n');
	return (0);
}
