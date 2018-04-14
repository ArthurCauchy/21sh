/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 09:37:44 by acauchy           #+#    #+#             */
/*   Updated: 2018/02/21 16:04:14 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_handler(int signo)
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

void		init_signals(void)
{
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		exit_error("System won't let us catch SIGINT.");
}
