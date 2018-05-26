#include "twenty_one_sh.h"

int	builtin_procs(t_env **env, char **args)
{
	(void)env;
	if (args[1])
	{
		ft_putendl_fd("procs: Too many arguments.", 2);
		return (1);
	}
	// save le nom du process (entre autres) ca serait cool
	if (g_shell.saved_pgid == -1)
	{
		ft_putendl_fd("No stopped process.", 2);
		return (1);
	}
	ft_putendl("Saved process groups :\nPGID");
	ft_putnbr(g_shell.saved_pgid);
	ft_putchar('\n');
	return (0);
}
