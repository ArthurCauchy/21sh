/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions_shiftarrowright.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:05:50 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/22 15:58:21 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	input_action_shiftarrowright(t_prompt_fct prompt_fct,
		t_inputdata *inputdata, t_history **history)
{
	(void)prompt_fct;
	(void)history;
	while (inputdata->cmd[inputdata->cur_cmd]
			&& inputdata->cmd[inputdata->cur_cmd] != ' ')
	{
		++inputdata->cur_cmd;
		go_forward(inputdata);
	}
	while (inputdata->cmd[inputdata->cur_cmd]
			&& inputdata->cmd[inputdata->cur_cmd] == ' ')
	{
		++inputdata->cur_cmd;
		go_forward(inputdata);
	}
}
