/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:48:57 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/01 17:37:49 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	init_shell(void)
{
	g_shell.exit_now = 0;
	g_shell.exit_status = 0;
	g_shell.env = NULL;
	g_shell.abort_command = 0;
	g_shell.shell_pgid = getpid();
	g_shell.pipe_lvl = 0;
	g_shell.pipe_pgid = -1;
	g_shell.pipe_processes = NULL;
	g_shell.saved_processes = NULL;
	if (setpgid(g_shell.shell_pgid, g_shell.shell_pgid) == -1)
		exit_error("Could not set the shell in it's own process group.");
	tcsetpgrp(0, g_shell.shell_pgid);
}

void	init_signals(void)
{
	ignore_signals();
	if (signal(SIGINT, sighandler) == SIG_ERR)
		exit_error("Can't catch SIGINT.");
}

void	init_env(t_env **env, char **envp)
{
	size_t	i;
	size_t	j;

	(void)env;
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j])
		{
			if (envp[i][j++] == '=')
			{
				set_env(env, ft_strsub(envp[i], 0, j - 1),
						ft_strdup(&envp[i][j]));
				break ;
			}
		}
		++i;
	}
}

void	init_builtins(void)
{
	load_builtin("exit", &builtin_exit);
	load_builtin("pwd", &builtin_pwd);
	load_builtin("cd", &builtin_cd);
	load_builtin("env", &builtin_env);
	load_builtin("setenv", &builtin_setenv);
	load_builtin("unsetenv", &builtin_unsetenv);
	load_builtin("echo", &builtin_echo);
	load_builtin("which", &builtin_which);
	load_builtin("procs", &builtin_procs);
	load_builtin("fg", &builtin_fg);
}
