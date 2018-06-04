/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_termios.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 14:19:50 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/04 16:37:37 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void tty_raw(void)
{
	struct termios raw;

	raw = g_shell.orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON);
	//raw.c_oflag &= ~(OPOST);
	raw.c_cc[VMIN] = 1; // what is this ?
	raw.c_cc[VTIME] = 0; // and that ?
	if (tcsetattr(0, TCSAFLUSH, &raw) < 0)
		exit_error("Can't set terminal to raw mode.");
}
