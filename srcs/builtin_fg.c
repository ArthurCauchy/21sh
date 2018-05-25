#include "twenty_one_sh.h"

int	builtin_fg(t_env **env, char **args)
{
	pid_t	pid;
	int		status;

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
	g_running_proc = pid;
	if (waitpid(pid, &status, WUNTRACED) == -1)
		exit_error("waitpid() error");
	g_running_proc = -1;
	return (post_process(pid, status));
}
