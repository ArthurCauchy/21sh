/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions_arrowup.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:05:50 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/12 16:28:55 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	input_action_arrowup(char *cmd, size_t *cur, t_termdata *termdata, t_history **history)
{
	t_history	*his;

	if (!*history)
		his = g_shell.history;
	else
		his = (*history)->next;
	if (!his)
		return ;
	ft_bzero(cmd, INPUT_MAX_LEN);
	*cur = 0;
	clear_cmd(termdata);
	while (his->cmd[*cur])
	{
		cmd[*cur] = his->cmd[*cur];
		++*cur;
	}
	print_cmd(cmd, termdata);
	*history = his;
}
