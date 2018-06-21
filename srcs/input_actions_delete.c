/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions_delete.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:05:50 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/21 16:10:43 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	input_action_delete(t_prompt_fct prompt_fct, t_inputdata *inputdata, t_history **history)
{
	size_t	i;

	(void)history;
	if (inputdata->cur_cmd > 0)
	{
		go_backward(inputdata);
		clear_cmd(inputdata);
		--inputdata->cur_cmd;
		i = inputdata->cur_cmd;
		while (inputdata->cmd[i])
		{
			inputdata->cmd[i] = inputdata->cmd[i + 1];
			++i;
		}
		print_cmd(prompt_fct, inputdata);
		restore_pos(inputdata);
	}
}
