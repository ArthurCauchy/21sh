/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 09:37:44 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/24 14:59:25 by acauchy          ###   ########.fr       */
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

static void	sigpipe_handler(int signo)
{
	if (signo == SIGPIPE)
	{
		// something helpful
	}
}

void		init_signals(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		exit_error("Can't catch SIGINT.");
	if (signal(SIGPIPE, sigpipe_handler) == SIG_ERR)
		exit_error("Can't catch SIGPIPE.");
}
