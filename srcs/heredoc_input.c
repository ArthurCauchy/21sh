/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 11:00:26 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/22 13:01:15 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

char	*ask_for_heredoc(void)
{
	int			read_size;
	t_inputdata	inputdata;
	static char	keybuff[KEYBUFF_SIZE];

	init_inputdata(&inputdata);
	ft_bzero(keybuff, KEYBUFF_SIZE);
	enable_raw_mode();
	print_cmd(&print_heredoc_prompt, &inputdata);
	while (!g_shell.input_cancel && (read_size = read(0, &keybuff, KEYBUFF_SIZE)) != 0)
	{
		if (g_shell.input_cancel == 1)
			continue ;
		if (read_size == -1)
			exit_error("read_error()");
		if (keybuff[0] == '\n')
			break ;
		if (inputdata.cur_cmd < INPUT_MAX_LEN - 2)
			heredoc_perform_actions(&print_heredoc_prompt, &inputdata, keybuff);
		ft_bzero(keybuff, KEYBUFF_SIZE);
	}
	while (inputdata.cur_row < inputdata.max_row)
	{
		ft_putstr(g_shell.termcaps->go_down);
		++inputdata.cur_row;
	}
	disable_raw_mode();
	if (g_shell.input_cancel)
	{
		g_shell.input_cancel = 0;
		return (NULL);
	}
	ft_putchar('\n');
	return (ft_strdup(inputdata.cmd));
}
