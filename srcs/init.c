/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:48:57 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/24 17:47:55 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	init_signals(void)
{
	ignore_signals();
	if (signal(SIGINT, sighandler) == SIG_ERR)
		exit_error("Can't catch SIGINT.");
	if (signal(SIGTSTP, sighandler) == SIG_ERR)
		exit_error("Can't catch SIGTSTP.");
	if (signal(SIGCHLD, sighandler) == SIG_ERR)
		exit_error("Can't catch SIGCHLD.");
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
}
