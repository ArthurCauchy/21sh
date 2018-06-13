/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termdata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 18:21:39 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/13 16:03:03 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	init_termdata(t_termdata *termdata)
{
	termdata->cur_col = 0;
	termdata->cur_row = 0;
	termdata->max_row = 0;
	termdata->saved_col = 0;
	termdata->saved_row = 0;
}

void	go_forward(t_termdata *termdata)
{
	if (termdata->cur_col == g_shell.nb_cols - 1)
	{
		ft_putstr(g_shell.termcaps->go_down);
		ft_putstr(tgoto(g_shell.termcaps->go_col, 0, 0));
		termdata->cur_col = 0;
		++termdata->cur_row;
	}
	else
	{
		ft_putstr(g_shell.termcaps->go_right);
		++termdata->cur_col;
	}
}

void	go_backward(t_termdata *termdata)
{
	if (termdata->cur_col == 0)
	{
		ft_putstr(g_shell.termcaps->go_up);
		ft_putstr(tgoto(g_shell.termcaps->go_col, 0, g_shell.nb_cols - 1));
		termdata->cur_col = g_shell.nb_cols - 1;
		--termdata->cur_row;
	}
	else
	{
		ft_putstr(g_shell.termcaps->go_left);
		--termdata->cur_col;
	}
}

void	restore_pos(t_termdata *termdata)
{
	while (termdata->cur_row != termdata->saved_row)
	{
		if (termdata->cur_row > termdata->saved_row)
		{
			ft_putstr(g_shell.termcaps->go_up);
			--termdata->cur_row;
		}
		else
		{
			ft_putstr(g_shell.termcaps->go_down);
			++termdata->cur_row;
		}
	}
	ft_putstr(tgoto(g_shell.termcaps->go_col, 0, termdata->saved_col));
	termdata->cur_col = termdata->saved_col;
}
