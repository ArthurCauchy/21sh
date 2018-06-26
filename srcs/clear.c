#include "twenty_one_sh.h"

void	clear_all(void)
{
	clear_env(*g_shell.env);
	clear_builtins();
	delete_history(g_shell.history);
	if (g_shell.saved_processes)
		delete_processes(g_shell.saved_processes);
	free(g_shell.termcaps);
}
