/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions_delete.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:05:50 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/11 19:36:03 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	input_action_delete(char *cmd, size_t *cur, t_termdata *termdata)
{
	size_t	i;

	clear_cmd(termdata);
	if (*cur > 0)
	{
		--*cur;
		i = *cur;
		while (cmd[i])
		{
			cmd[i] = cmd[i + 1];
			++i;
		}
	}
	print_cmd(cmd, termdata);
}
