/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions_shiftarrowleft.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:05:50 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/21 16:14:18 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	input_action_shiftarrowleft(t_prompt_fct prompt_fct,
		t_inputdata *inputdata, t_history **history)
{
	(void)prompt_fct;
	(void)history;
	while (inputdata->cur_cmd > 0 && inputdata->cmd[inputdata->cur_cmd] != ' ')
	{
		--inputdata->cur_cmd;
		go_backward(inputdata);
	}
	while (inputdata->cur_cmd > 0 && inputdata->cmd[inputdata->cur_cmd] == ' ')
	{
		--inputdata->cur_cmd;
		go_backward(inputdata);
	}
}
