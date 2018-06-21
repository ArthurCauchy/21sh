/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions_shifthome.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:05:50 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/21 16:17:13 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

/*
** copy
*/
void	input_action_shifthome(t_prompt_fct prompt_fct,
		t_inputdata *inputdata, t_history **history)
{
	(void)prompt_fct;
	(void)history;
	ft_bzero(g_shell.clipboard, INPUT_MAX_LEN);
	ft_strncpy(g_shell.clipboard, inputdata->cmd, inputdata->cur_cmd);
}
