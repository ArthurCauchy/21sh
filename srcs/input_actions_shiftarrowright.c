/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions_shiftarrowright.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:05:50 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/12 18:21:45 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	input_action_shiftarrowright(char *cmd, size_t *cur, t_termdata *termdata)
{
	while (cmd[*cur] && cmd[*cur] != ' ')
	{
		++*cur;
		go_forward(termdata);
	}
	while (cmd[*cur] && cmd[*cur] == ' ')
	{
		++*cur;
		go_forward(termdata);
	}
}
