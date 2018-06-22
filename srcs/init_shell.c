/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:48:57 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/22 11:15:50 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void			free_termcaps(t_termcaps *termcaps)
{
	if (termcaps->go_col)
		free(termcaps->go_col);
	if (termcaps->go_right)
		free(termcaps->go_right);
	if (termcaps->go_left)
		free(termcaps->go_left);
	if (termcaps->go_up)
		free(termcaps->go_up);
	if (termcaps->go_down)
		free(termcaps->go_down);
	if (termcaps->del_one_char)
		free(termcaps->del_one_char);
	if (termcaps->del_line)
		free(termcaps->del_line);
}

static t_termcaps	*init_termcaps(void)
{
	t_termcaps *new;

	if (!(new = (t_termcaps*)ft_memalloc(sizeof(t_termcaps))))
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
		free_termcaps(new);
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
	g_shell.input_cancel = 0;
	if (setpgid(g_shell.shell_pgid, g_shell.shell_pgid) == -1)
		exit_error("Could not set the shell in it's own process group.");
	if (tcgetattr(0, &g_shell.orig_termios) < 0)
		exit_error("Can't save tty settings.");
	tcsetpgrp(0, g_shell.shell_pgid);
	if (!(g_shell.termcaps = init_termcaps()))
		exit_error("Termcaps not fully supported.");
	g_shell.history = NULL;
	ft_bzero(g_shell.clipboard, INPUT_MAX_LEN);
	ft_bzero(g_shell.heredoc_fds, MAX_HEREDOC_TMP * sizeof(int));
}
