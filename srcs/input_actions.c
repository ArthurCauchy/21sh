/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:29:42 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/13 15:52:19 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	perform_actions_arrows(char *cmd, size_t *cur, t_termdata *termdata, char *keybuff, t_history **history)
{
	if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 65)
		input_action_arrowup(cmd, cur, termdata, history);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 66)
		input_action_arrowdown(cmd, cur, termdata, history);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 67)
		input_action_arrowright(cmd, cur, termdata, history);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 68)
		input_action_arrowleft(cmd, cur, termdata, history);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 49
			&& keybuff[3] == 59 && keybuff[4] == 50 && keybuff[5] == 67)
		input_action_shiftarrowright(cmd, cur, termdata, history);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 49
			&& keybuff[3] == 59 && keybuff[4] == 50 && keybuff[5] == 65)
		input_action_shiftarrowup(cmd, cur, termdata, history);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 49
			&& keybuff[3] == 59 && keybuff[4] == 50 && keybuff[5] == 66)
		input_action_shiftarrowdown(cmd, cur, termdata, history);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 49
			&& keybuff[3] == 59 && keybuff[4] == 50 && keybuff[5] == 68)
		input_action_shiftarrowleft(cmd, cur, termdata, history);
	else
		return (0);
	return (1);
}

void	perform_actions(char *cmd, size_t *cur, t_termdata *termdata, char *keybuff, t_history **history)
{
	if (perform_actions_arrows(cmd, cur, termdata, keybuff, history))
		(void)0;
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 72)
		input_action_home(cmd, cur, termdata, history);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 70)
		input_action_end(cmd, cur, termdata, history);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 49
			&& keybuff[3] == 59 && keybuff[4] == 50 && keybuff[5] == 72)
		input_action_shifthome(cmd, cur, termdata, history);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 49
			&& keybuff[3] == 59 && keybuff[4] == 50 && keybuff[5] == 70)
		input_action_shiftend(cmd, cur, termdata, history);
	else if (keybuff[0] == 127)
		input_action_delete(cmd, cur, termdata, history);
	else if (ft_isprint(keybuff[0]))
		add_to_input(cmd, cur, termdata, keybuff);
	else
		printf("%02d %02d %02d %02d %02d %02d %02d %02d\n", keybuff[0], keybuff[1], keybuff[2], keybuff[3], keybuff[4], keybuff[5], keybuff[6], keybuff[7]);
}
