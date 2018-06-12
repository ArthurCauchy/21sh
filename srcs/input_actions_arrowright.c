/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions_arrowright.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:05:50 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/12 16:27:28 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	input_action_arrowright(char *cmd, size_t *cur, t_termdata *termdata)
{
	if (cmd[*cur])
	{
		++*cur;
		go_forward(termdata);
	}
}
