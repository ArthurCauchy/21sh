/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions_shiftend.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:05:50 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/19 14:14:35 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	input_action_shiftend(t_inputdata *inputdata, t_history **history)
{
	char	*tmp;
	size_t	i;

	(void)history;
	if (!g_shell.clipboard[0])
		return ;
	tmp = ft_strdup(inputdata->cmd + inputdata->cur_cmd);
	i = 0;
	while (i++ < ft_strlen(g_shell.clipboard))
		go_forward(inputdata);
	clear_cmd(inputdata);
	i = 0;
	while (inputdata->cur_cmd < INPUT_MAX_LEN - 2 &&
			i < ft_strlen(g_shell.clipboard))
	{
		inputdata->cmd[inputdata->cur_cmd] = g_shell.clipboard[i];
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
