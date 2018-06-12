/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions_arrowleft.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:05:50 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/12 16:28:55 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	input_action_arrowleft(char *cmd, size_t *cur, t_termdata *termdata)
{
	(void)cmd;
	if (*cur > 0)
	{
		--*cur;
		go_backward(termdata);
	}
}
