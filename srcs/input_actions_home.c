/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions_home.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:05:50 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/21 16:15:56 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	input_action_home(t_prompt_fct prompt_fct,
		t_inputdata *inputdata, t_history **history)
{
	(void)prompt_fct;
	(void)history;
	while (inputdata->cur_cmd > 0)
	{
		go_backward(inputdata);
		--inputdata->cur_cmd;
	}
}
