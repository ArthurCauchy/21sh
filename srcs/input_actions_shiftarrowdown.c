/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions_shiftarrowdown.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:05:50 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/13 13:47:48 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	input_action_shiftarrowdown(char *cmd, size_t *cur, t_termdata *termdata)
{
	int	i;

	(void)cmd;
	i = 0;
	while (cmd[*cur] > 0 && i < g_shell.nb_cols)
	{
		++*cur;
		go_forward(termdata);
		++i;
	}
}
