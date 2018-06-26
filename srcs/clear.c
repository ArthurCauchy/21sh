/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 15:03:54 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/26 15:03:56 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	clear_all(void)
{
	clear_env(*g_shell.env);
	clear_builtins();
	delete_history(g_shell.history);
	if (g_shell.saved_processes)
		delete_processes(g_shell.saved_processes);
	free(g_shell.termcaps);
}
