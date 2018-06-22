/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions_arrowup.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:05:50 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/22 15:56:29 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	input_action_arrowup(t_prompt_fct prompt_fct,
		t_inputdata *inputdata, t_history **history)
{
	t_history	*his;

	if (!*history)
		his = g_shell.history;
	else
		his = (*history)->next;
	if (!his)
		return ;
	ft_bzero(inputdata->cmd, INPUT_MAX_LEN);
	inputdata->cur_cmd = 0;
	clear_cmd(inputdata);
	while (his->cmd[inputdata->cur_cmd])
	{
		inputdata->cmd[inputdata->cur_cmd] = his->cmd[inputdata->cur_cmd];
		++inputdata->cur_cmd;
	}
	print_cmd(prompt_fct, inputdata);
	*history = his;
}
