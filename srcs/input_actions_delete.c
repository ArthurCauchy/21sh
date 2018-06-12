/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions_delete.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:05:50 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/12 16:42:55 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	input_action_delete(char *cmd, size_t *cur, t_termdata *termdata)
{
	size_t	i;

	if (*cur > 0)
	{
		go_backward(termdata);
		clear_cmd(termdata);
		--*cur;
		i = *cur;
		while (cmd[i])
		{
			cmd[i] = cmd[i + 1];
			++i;
		}
		print_cmd(cmd, termdata);
		restore_pos(termdata);
	}
}
