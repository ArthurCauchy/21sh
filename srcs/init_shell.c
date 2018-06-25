/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:48:57 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/25 16:54:17 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void				init_shell(void)
{
	g_shell.exit_now = 0;
	g_shell.exit_status = 0;
	g_shell.env = NULL;
	g_shell.last_command_status = 0;
	g_shell.abort_command = 0;
	g_shell.shell_pgid = getpid();
	g_shell.pipe_lvl = 0;
	g_shell.pipe_pgid = -1;
	g_shell.pipe_processes = NULL;
	g_shell.saved_processes = NULL;
	g_shell.nb_cols = get_term_cols();
	if (setpgid(g_shell.shell_pgid, g_shell.shell_pgid) == -1)
		exit_error("Could not set the shell in it's own process group.");
	if (tcgetattr(0, &g_shell.orig_termios) < 0)
		exit_error("Can't save tty settings.");
	tcsetpgrp(0, g_shell.shell_pgid);
	if (!(g_shell.termcaps = load_termcaps()))
		exit_error("Termcaps not fully supported.");
	g_shell.history = NULL;
	ft_bzero(g_shell.clipboard, INPUT_MAX_LEN);
	ft_bzero(g_shell.heredoc_fds, sizeof(int) * MAX_HEREDOC_TMP);
}
