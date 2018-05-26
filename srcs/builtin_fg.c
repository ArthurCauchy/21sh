#include "twenty_one_sh.h"

int	builtin_fg(t_env **env, char **args)
{
	pid_t	pgid;
	int		status;

	(void)env;
	if (args[1])
	{
		ft_putendl_fd("fg: Too many arguments.", 2);
		return (1);
	}
	if ((pgid = restore_process()) == -1)
	{
		ft_putendl_fd("No stopped process.", 2);
		return (1);
	}
	g_shell.saved_pgid = -1;
	if (waitpid(-pgid, &status, WUNTRACED) == -1)
		exit_error("waitpid() error");
	return (post_process(pgid, status));
}
