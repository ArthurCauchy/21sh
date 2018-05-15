/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:48:57 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/15 11:30:59 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	init_shell(void)
{
	g_shell.terminal = STDIN_FILENO;
	g_shell.is_interactive = isatty(g_shell.terminal);
	if (g_shell.is_interactive)
	{
		while (tcgetpgrp(g_shell.terminal) != (g_shell.pgid = getpgrp()))
			kill(- g_shell.pgid, SIGTTIN);
		g_shell.pgid = getpid();
		if (setpgid(g_shell.pgid, g_shell.pgid) == -1)
		{
			ft_putendl_fd("Couldn't put the shell in its own process group", 2);
			exit(1); // peut etre un peu moins violent ?
		}
		/* Grab control of the terminal.  */
		tcsetpgrp(g_shell.terminal, g_shell.pgid);

		/* Save default terminal attributes for shell.  */
		tcgetattr(g_shell.terminal, &g_shell.tmodes);
	}
}

void	init_signals(void)
{
	//signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
	register_signals();
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
}
