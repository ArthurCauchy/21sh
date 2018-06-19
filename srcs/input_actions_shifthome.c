/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions_shifthome.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:05:50 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/19 12:00:55 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	input_action_shifthome(t_inputdata *inputdata, t_history **history)
{
	(void)history;
	ft_bzero(inputdata->clipboard, INPUT_MAX_LEN);
	ft_strncpy(inputdata->clipboard, inputdata->cmd, inputdata->cur_cmd);
}
