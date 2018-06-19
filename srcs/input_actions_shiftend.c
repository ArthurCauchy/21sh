/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions_shiftend.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:05:50 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/19 12:33:52 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	input_action_shiftend(t_inputdata *inputdata, t_history **history)
{
	char	*tmp;
	size_t	i;

	(void)history;
	if (!inputdata->clipboard[0])
		return ;
	tmp = ft_strdup(inputdata->cmd + inputdata->cur_cmd);
	clear_cmd(inputdata);
	i = 0;
	while (inputdata->cur_cmd < INPUT_MAX_LEN - 2 &&
			i < ft_strlen(inputdata->clipboard))
	{
		inputdata->cmd[inputdata->cur_cmd] = inputdata->clipboard[i];
		++i;
		++inputdata->cur_cmd;
	}
	i = 0;
	while (inputdata->cur_cmd < INPUT_MAX_LEN - 2 && i < ft_strlen(tmp))
	{
		inputdata->cmd[inputdata->cur_cmd] = tmp[i];
		++i;
		++inputdata->cur_cmd;
	}
	free(tmp);
	print_cmd(inputdata);
	restore_pos(inputdata);
}
