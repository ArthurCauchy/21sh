/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:48:57 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/11 17:59:36 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static t_termcaps	*init_termcaps(void)
{
	t_termcaps *new;

	if (!(new = (t_termcaps*)malloc(sizeof(t_termcaps))))
		exit_error("malloc() error");
	new->go_col = tgetstr("ch", NULL);
	new->go_right = tgetstr("nd", NULL);
	new->go_left = tgetstr("le", NULL);
	new->go_up = tgetstr("up", NULL);
	new->go_down = tgetstr("do", NULL);
	new->del_one_char = tgetstr("dc", NULL);
	new->del_line = tgetstr("ce", NULL);
	if (!new->go_col || !new->go_left || !new->del_one_char
			|| !new->go_up || !new->go_down || !new->del_one_char
			|| !new->del_line)
	{
		// check fuites memoire si le premier termcap existe mais pas les autres
		free(new);
		return (NULL);
	}
	return (new);
}

void	init_shell(void)
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
	g_shell.cmd_cancel = 0;
	if (setpgid(g_shell.shell_pgid, g_shell.shell_pgid) == -1)
		exit_error("Could not set the shell in it's own process group.");
	if (tcgetattr(0, &g_shell.orig_termios) < 0)
		exit_error("Can't save tty settings.");
	tcsetpgrp(0, g_shell.shell_pgid);
	if (!(g_shell.termcaps = init_termcaps()))
		exit_error("Termcaps not fully supported.");
	g_shell.history = NULL;
}
