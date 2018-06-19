/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:29:42 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/19 15:47:10 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	perform_actions_arrows(t_inputdata *inputdata, char *keybuff, t_history **history)
{
	if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 65)
		input_action_arrowup(inputdata, history);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 66)
		input_action_arrowdown(inputdata, history);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 67)
		input_action_arrowright(inputdata, history);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 68)
		input_action_arrowleft(inputdata, history);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 49
			&& keybuff[3] == 59 && keybuff[4] == 50 && keybuff[5] == 67)
		input_action_shiftarrowright(inputdata, history);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 49
			&& keybuff[3] == 59 && keybuff[4] == 50 && keybuff[5] == 65)
		input_action_shiftarrowup(inputdata, history);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 49
			&& keybuff[3] == 59 && keybuff[4] == 50 && keybuff[5] == 66)
		input_action_shiftarrowdown(inputdata, history);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 49
			&& keybuff[3] == 59 && keybuff[4] == 50 && keybuff[5] == 68)
		input_action_shiftarrowleft(inputdata, history);
	else
		return (0);
	return (1);
}

void	perform_actions(t_inputdata *inputdata, char *keybuff, t_history **history)
{
	if (perform_actions_arrows(inputdata, keybuff, history))
		(void)0;
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 72)
		input_action_home(inputdata, history);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 70)
		input_action_end(inputdata, history);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 49
			&& keybuff[3] == 59 && keybuff[4] == 50 && keybuff[5] == 72)
		input_action_shifthome(inputdata, history);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 49
			&& keybuff[3] == 59 && keybuff[4] == 50 && keybuff[5] == 70)
		input_action_shiftend(inputdata, history);
	else if (keybuff[0] == 127)
		input_action_delete(inputdata, history);
	else if (keybuff[0] == 4)
		input_action_del(inputdata, history);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 51 && keybuff[3] == 126)
		input_action_del(inputdata, history);
	else if (ft_isprint(keybuff[0]))
		add_to_input(inputdata, keybuff);
	else
		printf("%02d %02d %02d %02d %02d %02d %02d %02d\n", keybuff[0], keybuff[1], keybuff[2], keybuff[3], keybuff[4], keybuff[5], keybuff[6], keybuff[7]);
}
