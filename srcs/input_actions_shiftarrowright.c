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

void	input_action_shiftarrowright(t_inputdata *inputdata, t_history **history)
{
	(void)history;
	while (inputdata->cmd[inputdata->cur_cmd] && inputdata->cmd[inputdata->cur_cmd] != ' ')
	{
		++inputdata->cur_cmd;
		go_forward(inputdata);
	}
	while (inputdata->cmd[inputdata->cur_cmd] && inputdata->cmd[inputdata->cur_cmd] == ' ')
	{
		++inputdata->cur_cmd;
		go_forward(inputdata);
	}
}
