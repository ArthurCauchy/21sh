/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input_actions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:29:42 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/21 17:36:36 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	perform_actions_arrows(t_prompt_fct prompt_fct, t_inputdata *inputdata,
		char *keybuff)
{
	if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 67)
		input_action_arrowright(prompt_fct, inputdata, NULL);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 68)
		input_action_arrowleft(prompt_fct, inputdata, NULL);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 49
			&& keybuff[3] == 59 && keybuff[4] == 50 && keybuff[5] == 67)
		input_action_shiftarrowright(prompt_fct, inputdata, NULL);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 49
			&& keybuff[3] == 59 && keybuff[4] == 50 && keybuff[5] == 65)
		input_action_shiftarrowup(prompt_fct, inputdata, NULL);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 49
			&& keybuff[3] == 59 && keybuff[4] == 50 && keybuff[5] == 66)
		input_action_shiftarrowdown(prompt_fct, inputdata, NULL);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 49
			&& keybuff[3] == 59 && keybuff[4] == 50 && keybuff[5] == 68)
		input_action_shiftarrowleft(prompt_fct, inputdata, NULL);
	else
		return (0);
	return (1);
}

void	heredoc_perform_actions(t_prompt_fct prompt_fct, t_inputdata *inputdata,
		char *keybuff)
{
	if (perform_actions_arrows(prompt_fct, inputdata, keybuff))
		(void)0;
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 72)
		input_action_home(prompt_fct, inputdata, NULL);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 70)
		input_action_end(prompt_fct, inputdata, NULL);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 49
			&& keybuff[3] == 59 && keybuff[4] == 50 && keybuff[5] == 72)
		input_action_shifthome(prompt_fct, inputdata, NULL);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 90)
		input_action_shifttab(prompt_fct, inputdata, NULL);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 49
			&& keybuff[3] == 59 && keybuff[4] == 50 && keybuff[5] == 70)
		input_action_shiftend(prompt_fct, inputdata, NULL);
	else if (keybuff[0] == 127)
		input_action_delete(prompt_fct, inputdata, NULL);
	else if (keybuff[0] == 4)
		input_action_del(prompt_fct, inputdata, NULL);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 51 && keybuff[3] == 126)
		input_action_del(prompt_fct, inputdata, NULL);
	else if (ft_isprint(keybuff[0]))
		add_to_input(prompt_fct, inputdata, keybuff);
}
