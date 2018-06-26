/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 11:00:26 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/26 15:19:14 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

/*
** return : 1 = stop reading keypresses
*/

static void	heredoc_input_loop(t_inputdata *inputdata, int *cancel)
{
	int			read_size;
	static char	keybuff[KEYBUFF_SIZE];

	ft_bzero(keybuff, KEYBUFF_SIZE);
	while ((read_size = read(0, &keybuff, KEYBUFF_SIZE)) != 0)
	{
		if (keybuff[0] == 3)
		{
			*cancel = 1;
			break ;
		}
		if (keybuff[0] == '\n')
			break ;
		if (inputdata->cur_cmd < INPUT_MAX_LEN - 2)
			heredoc_perform_actions(&print_heredoc_prompt, inputdata, keybuff);
		ft_bzero(keybuff, KEYBUFF_SIZE);
	}
}

char		*ask_for_heredoc(void)
{
	int			cancel;
	t_inputdata	inputdata;

	cancel = 0;
	init_inputdata(&inputdata);
	enable_raw_mode();
	print_cmd(&print_heredoc_prompt, &inputdata);
	heredoc_input_loop(&inputdata, &cancel);
	while (inputdata.cur_row < inputdata.max_row)
	{
		ft_putstr(g_shell.termcaps->go_down);
		++inputdata.cur_row;
	}
	disable_raw_mode();
	ft_putchar('\n');
	if (cancel)
		return (NULL);
	return (ft_strdup(inputdata.cmd));
}
