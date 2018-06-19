/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions_shifthome.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:05:50 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/19 16:11:06 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

/*
** copy
*/
void	input_action_shifthome(t_inputdata *inputdata, t_history **history)
{
	(void)history;
	ft_bzero(g_shell.clipboard, INPUT_MAX_LEN);
	ft_strncpy(g_shell.clipboard, inputdata->cmd, inputdata->cur_cmd);
}
