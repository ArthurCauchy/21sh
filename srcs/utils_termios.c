/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_termios.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 14:19:50 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/22 15:46:06 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	enable_raw_mode(void)
{
	struct termios raw;

	raw = g_shell.orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON | ISIG);
	raw.c_oflag &= ~(OPOST);
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSAFLUSH, &raw) < 0)
		exit_error("Can't set terminal to raw mode.");
}

void	disable_raw_mode(void)
{
	if (tcsetattr(0, TCSAFLUSH, &g_shell.orig_termios) < 0)
		exit_error("Can't set terminal back to default mode.");
}

#ifdef TIOCGSIZE

int		get_term_cols(void)
{
	struct ttysize	ts;

	ioctl(0, TIOCGSIZE, &ts);
	return (ts.ts_cols);
}

#else

int		get_term_cols(void)
{
	struct winsize	ws;

	ioctl(0, TIOCGWINSZ, &ws);
	return (ws.ws_col);
}

#endif
