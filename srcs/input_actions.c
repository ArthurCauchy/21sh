/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:29:42 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/09 17:44:27 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	perform_actions(char *line, size_t *cur, char *keybuff)
{
	if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 72)
		ft_putstr("home");
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 70)
		ft_putstr("end");
	else if (keybuff[0] == 127)
		input_action_delete(line, cur);
	else if (keybuff[0] == 4)
		ft_putstr("ctrl+d");
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 65)
		ft_putstr("arrowup");
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 66)
		ft_putstr("arrowdown");
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 67)
		input_action_arrowright(line, cur);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 68)
		input_action_arrowleft(line, cur);
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 49
			&& keybuff[3] == 59 && keybuff[4] == 50 && keybuff[5] == 67)
		ft_putstr("shift+arrowright");
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 49
			&& keybuff[3] == 59 && keybuff[4] == 50 && keybuff[5] == 68)
		ft_putstr("shift+arrowleft");
	else if (keybuff[0] == 27 && keybuff[1] == 0) //tmp
		exit(42);
	else if (ft_isprint(keybuff[0]))
		add_to_input(line, cur, keybuff);
	else
		printf("%02d %02d %02d %02d %02d %02d %02d %02d\n", keybuff[0], keybuff[1], keybuff[2], keybuff[3], keybuff[4], keybuff[5], keybuff[6], keybuff[7]);
}
