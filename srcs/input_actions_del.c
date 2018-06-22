/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions_del.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:05:50 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/22 15:57:12 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	input_action_del(t_prompt_fct prompt_fct,
		t_inputdata *inputdata, t_history **history)
{
	size_t	i;

	(void)history;
	if (inputdata->cur_cmd < (int)ft_strlen(inputdata->cmd))
	{
		clear_cmd(inputdata);
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
