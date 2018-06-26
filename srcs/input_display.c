/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 09:37:26 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/26 15:22:04 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	clear_cmd(t_inputdata *inputdata)
{
	inputdata->saved_col = inputdata->cur_col;
	inputdata->saved_row = inputdata->cur_row;
	while (inputdata->cur_row < inputdata->max_row)
	{
		ft_putstr(g_shell.termcaps->go_down);
		++inputdata->cur_row;
	}
	while (inputdata->cur_row >= 0)
	{
		ft_putstr(tgoto(g_shell.termcaps->go_col, 0, 0));
		ft_putstr(g_shell.termcaps->del_line);
		if (inputdata->cur_row > 0)
			ft_putstr(g_shell.termcaps->go_up);
		--inputdata->cur_row;
	}
	inputdata->cur_col = 0;
	inputdata->cur_row = 0;
	inputdata->max_row = 0;
}

void	print_cmd(t_prompt_fct prompt_fct, t_inputdata *inputdata)
{
	size_t	i;

	i = 0;
	inputdata->cur_col = prompt_fct(g_shell.env);
	while (inputdata->cmd[i])
	{
		ft_putchar(inputdata->cmd[i]);
		if (inputdata->cur_col == g_shell.nb_cols - 1)
		{
			ft_putstr(g_shell.termcaps->go_down);
			ft_putstr(tgoto(g_shell.termcaps->go_col, 0, 0));
			inputdata->cur_col = 0;
			++inputdata->cur_row;
			++inputdata->max_row;
		}
		else
			++inputdata->cur_col;
		++i;
	}
}
