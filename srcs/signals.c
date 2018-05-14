/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 09:37:44 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/14 14:00:39 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putchar('\n');
		if (g_running_proc == -1)
		{
			print_prompt(g_envptr);
		}
	}
}

void		register_signals(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		exit_error("Can't catch SIGINT.");
}

void		reset_signals_actions(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}
