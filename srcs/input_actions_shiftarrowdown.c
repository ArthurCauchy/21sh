/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions_shiftarrowdown.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:05:50 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/13 13:47:48 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	input_action_shiftarrowdown(t_inputdata *inputdata, t_history **history)
{
	int	i;

	(void)history;
	i = 0;
	while (inputdata->cmd[inputdata->cur_cmd] > 0 && i < g_shell.nb_cols)
	{
		++inputdata->cur_cmd;
		go_forward(inputdata);
		++i;
	}
}
