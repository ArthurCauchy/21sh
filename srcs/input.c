/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 09:37:26 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/20 11:04:10 by acauchy          ###   ########.fr       */
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

void	print_cmd(t_inputdata *inputdata)
{
	size_t	i;

	i = 0;
	
	inputdata->cur_col = print_prompt(g_shell.env);
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

void	add_to_input(t_inputdata *inputdata, char *keybuff)
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
	print_cmd(inputdata);
	restore_pos(inputdata);
}

char	*ask_for_input(void)
{
	int			read_size;
	t_inputdata	inputdata;
	static char	keybuff[KEYBUFF_SIZE];
	t_history	*history;

	init_inputdata(&inputdata);
	ft_bzero(keybuff, KEYBUFF_SIZE);
	history = NULL;
	enable_raw_mode();
	print_cmd(&inputdata);
	while ((read_size = read(0, &keybuff, KEYBUFF_SIZE)) != 0) // mettre ca dans une fct static
	{
		if (g_shell.input_cancel == 1)
		{
			g_shell.nb_cols = get_term_cols();
			init_inputdata(&inputdata);
			inputdata.cur_col = print_prompt(g_shell.env);
			g_shell.input_cancel = 0;
		}
		if (read_size == -1)
			exit_error("read() error");
		if (keybuff[0] == '\n')
			break ;
		else if (keybuff[0] == 4 && inputdata.cur_cmd == (int)ft_strlen(inputdata.cmd))
		{
			if (!inputdata.cmd[0])
				ft_strcpy(inputdata.cmd, "exit");
			else
				ft_bzero(inputdata.cmd, INPUT_MAX_LEN);
			break ;
		}
		if (inputdata.cur_cmd < INPUT_MAX_LEN - 2)
			perform_actions(&inputdata, keybuff, &history);
		ft_bzero(keybuff, KEYBUFF_SIZE);
	}
	while (inputdata.cur_row < inputdata.max_row) // put this in a static fct too
	{
		ft_putstr(g_shell.termcaps->go_down);
		++inputdata.cur_row;
	}
	disable_raw_mode();
	ft_putchar('\n');
	return (ft_strdup(inputdata.cmd));
}
