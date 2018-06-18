/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions_arrowdown.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:05:50 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/12 16:28:55 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	input_action_arrowdown(t_inputdata *inputdata, t_history **history)
{
	t_history	*his;

	if (!*history)
		return ;
	else
		his = (*history)->prev;
	ft_bzero(inputdata->cmd, INPUT_MAX_LEN);
	inputdata->cur_cmd = 0;
	clear_cmd(inputdata);
	if (his)
	{
		while (his->cmd[inputdata->cur_cmd])
		{
			inputdata->cmd[inputdata->cur_cmd] = his->cmd[inputdata->cur_cmd];
			++inputdata->cur_cmd;
		}
	}
	print_cmd(inputdata);
	*history = his;
}
