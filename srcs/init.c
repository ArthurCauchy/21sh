/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:48:57 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/22 15:24:51 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void	init_tty(void)
{
	char	*term_type;
	int		success;

	if (!isatty(0))
		exit_error("Not a tty !");
	term_type = getenv("TERM");
	if ((success = tgetent(NULL, term_type)) < 0)
		exit_error("Can't access termcap database.");
	else if (success == 0)
		exit_error("This terminal type is not defined.");
}

void		init(t_env **env, char **envp)
{
	ignore_signals();
	init_tty();
	init_shell();
	init_builtins();
	init_env(env, envp);
	g_shell.env = env;
}
