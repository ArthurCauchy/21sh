#include "twenty_one_sh.h"

int	builtin_procs(t_env **env, char **args)
{
	t_process	*cur;
	int			pid;

	(void)env;
	if (args[1])
	{
		ft_putendl_fd("procs: Too many arguments.", 2);
		return (1);
	}
	// save le nom du process (entre autres) ca serait cool
	if (!g_shell.saved_processes)
	{
		ft_putendl_fd("No stopped process.", 2);
		return (1);
	}
	cur = g_shell.saved_processes;
	while (cur)
	{
		pid = cur->pid;
		ft_fminiprint(1, "%l6d% %l0s%\n", &pid, cur->args[0]); // print args too ?
		cur = cur->next;
	}
	return (0);
}
