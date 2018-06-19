/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputdata.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 18:21:39 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/19 14:01:22 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	init_inputdata(t_inputdata *inputdata)
{
	ft_bzero(inputdata->cmd, INPUT_MAX_LEN);
	inputdata->cur_cmd = 0;
	inputdata->cur_col = 0;
	inputdata->cur_row = 0;
	inputdata->max_row = 0;
	inputdata->saved_col = 0;
	inputdata->saved_row = 0;
}

void	go_forward(t_inputdata *inputdata)
{
	if (inputdata->cur_col == g_shell.nb_cols - 1)
	{
		ft_putstr(g_shell.termcaps->go_down);
		ft_putstr(tgoto(g_shell.termcaps->go_col, 0, 0));
		inputdata->cur_col = 0;
		++inputdata->cur_row;
	}
	else
	{
		ft_putstr(g_shell.termcaps->go_right);
		++inputdata->cur_col;
	}
}

void	go_backward(t_inputdata *inputdata)
{
	if (inputdata->cur_col == 0)
	{
		ft_putstr(g_shell.termcaps->go_up);
		ft_putstr(tgoto(g_shell.termcaps->go_col, 0, g_shell.nb_cols - 1));
		inputdata->cur_col = g_shell.nb_cols - 1;
		--inputdata->cur_row;
	}
	else
	{
		ft_putstr(g_shell.termcaps->go_left);
		--inputdata->cur_col;
	}
}

void	restore_pos(t_inputdata *inputdata)
{
	while (inputdata->cur_row != inputdata->saved_row)
	{
		if (inputdata->cur_row > inputdata->saved_row)
		{
			ft_putstr(g_shell.termcaps->go_up);
			--inputdata->cur_row;
		}
		else
		{
			ft_putstr(g_shell.termcaps->go_down);
			++inputdata->cur_row;
		}
	}
	ft_putstr(tgoto(g_shell.termcaps->go_col, 0, inputdata->saved_col));
	inputdata->cur_col = inputdata->saved_col;
}
