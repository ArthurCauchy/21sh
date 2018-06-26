/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 09:37:26 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/26 15:39:11 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void		add_to_input(t_prompt_fct prompt_fct,
		t_inputdata *inputdata, char *keybuff)
{
	int	i;

	go_forward(inputdata);
	clear_cmd(inputdata);
	if (inputdata->cmd[0])
	{
		i = ft_strlen(inputdata->cmd) - 1;
		while (i >= inputdata->cur_cmd)
		{
			inputdata->cmd[i + 1] = inputdata->cmd[i];
			if (i == 0)
				break ;
			--i;
		}
	}
	inputdata->cmd[inputdata->cur_cmd] = keybuff[0];
	++inputdata->cur_cmd;
	print_cmd(prompt_fct, inputdata);
	restore_pos(inputdata);
}

/*
** if returns 1, it means the line is empty and we should exit the shell
*/

static int	handle_ctrl_d(t_inputdata *inputdata)
{
	if (!inputdata->cmd[0])
	{
		ft_strcpy(inputdata->cmd, "exit");
		return (1);
	}
	ft_putchar('\n');
	ft_putstr(tgoto(g_shell.termcaps->go_col, 0, 0));
	inputdata->saved_col = inputdata->cur_col;
	inputdata->saved_row = inputdata->cur_row;
	inputdata->cur_col = 0;
	inputdata->cur_row = 0;
	inputdata->max_row = 0;
	print_cmd(&print_prompt, inputdata);
	restore_pos(inputdata);
	return (0);
}

static void	input_loop(t_inputdata *inputdata, t_history *history)
{
	int			read_size;
	static char	keybuff[KEYBUFF_SIZE];

	ft_bzero(keybuff, KEYBUFF_SIZE);
	while ((read_size = read(0, &keybuff, KEYBUFF_SIZE)) != 0)
	{
		if (keybuff[0] == 3)
		{
			inputdata->cmd[0] = '\0';
			break ;
		}
		if (keybuff[0] == '\n')
			break ;
		else if (keybuff[0] == 4 &&
				inputdata->cur_cmd == (int)ft_strlen(inputdata->cmd))
		{
			if (handle_ctrl_d(inputdata) == 1)
				break ;
		}
		else if (inputdata->cur_cmd < INPUT_MAX_LEN - 2)
			perform_actions(&print_prompt, inputdata, keybuff, &history);
		ft_bzero(keybuff, KEYBUFF_SIZE);
	}
}

char		*ask_for_input(void)
{
	t_inputdata	inputdata;
	t_history	*history;

	init_inputdata(&inputdata);
	history = NULL;
	enable_raw_mode();
	print_cmd(&print_prompt, &inputdata);
	input_loop(&inputdata, history);
	while (inputdata.cur_row < inputdata.max_row)
	{
		ft_putstr(g_shell.termcaps->go_down);
		++inputdata.cur_row;
	}
	disable_raw_mode();
	ft_putchar('\n');
	return (ft_strdup(inputdata.cmd));
}
