/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions_shiftarrowup.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:05:50 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/13 13:47:40 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	input_action_shiftarrowup(char *cmd, size_t *cur, t_termdata *termdata, t_history **history)
{
	int	i;

	(void)cmd;
	(void)history;
	i = 0;
	while (*cur > 0 && i < g_shell.nb_cols)
	{
		--*cur;
		go_backward(termdata);
		++i;
	}
}
