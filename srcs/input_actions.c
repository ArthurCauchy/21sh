/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:29:42 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/08 17:29:34 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	perform_actions(char *keybuff)
{
	if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 72)
		ft_putendl("home");
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 70)
		ft_putendl("end");
	else if (keybuff[0] == 9)
		ft_putendl("tab");
	else if (keybuff[0] == 4)
		ft_putendl("ctrl+d");
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 65)
		ft_putendl("arrowup");
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 66)
		ft_putendl("arrowdown");
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 67)
		ft_putendl("arrowright");
	else if (keybuff[0] == 27 && keybuff[1] == 91 && keybuff[2] == 68)
		ft_putendl("arrowleft");
	else
		printf("%02d %02d %02d %02d %02d %02d %02d\n", keybuff[0], keybuff[1], keybuff[2], keybuff[3], keybuff[4], keybuff[5], keybuff[6]);
}
