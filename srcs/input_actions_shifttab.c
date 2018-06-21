/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions_shifttab.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:05:50 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/21 16:17:39 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

/*
** cut
*/
void	input_action_shifttab(t_prompt_fct prompt_fct,
		t_inputdata *inputdata, t_history **history)
{
	char	*tmp;

	(void)history;
	ft_bzero(g_shell.clipboard, INPUT_MAX_LEN);
	ft_strncpy(g_shell.clipboard, inputdata->cmd, inputdata->cur_cmd);
	tmp = ft_strdup(inputdata->cmd + inputdata->cur_cmd);
	while (inputdata->cur_cmd-- > 0)
		go_backward(inputdata);
	clear_cmd(inputdata);
	ft_bzero(inputdata->cmd, INPUT_MAX_LEN);
	inputdata->cur_cmd = 0;
	ft_strncpy(inputdata->cmd, tmp, INPUT_MAX_LEN);
	free(tmp);
	print_cmd(prompt_fct, inputdata);
	restore_pos(inputdata);
}
