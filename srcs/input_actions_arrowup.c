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
	if (history)
	{
		ft_bzero(cmd, INPUT_MAX_LEN);
		*cur = 0;
		clear_cmd(termdata);
		while ((*history)->cmd[*cur])
		{
			cmd[*cur] = (*history)->cmd[*cur];
			++*cur;
		}
		*history = (*history)->next;
		print_cmd(cmd, termdata);
	}
}
