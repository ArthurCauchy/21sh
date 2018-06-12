/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions_shiftarrowleft.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:05:50 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/12 18:21:44 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	input_action_shiftarrowleft(char *cmd, size_t *cur, t_termdata *termdata)
{
	while (*cur > 0 && cmd[*cur] != ' ')
	{
		--*cur;
		go_backward(termdata);
	}
	while (*cur > 0 && cmd[*cur] == ' ')
	{
		--*cur;
		go_backward(termdata);
	}
}
