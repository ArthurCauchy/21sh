/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions_shiftarrowup.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:05:50 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/21 16:15:11 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	input_action_shiftarrowup(t_prompt_fct prompt_fct,
		t_inputdata *inputdata, t_history **history)
{
	int	i;

	(void)prompt_fct;
	(void)history;
	i = 0;
	while (inputdata->cur_cmd > 0 && i < g_shell.nb_cols)
	{
		--inputdata->cur_cmd;
		go_backward(inputdata);
		++i;
	}
}
