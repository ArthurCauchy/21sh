/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 09:37:26 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/11 19:51:31 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

/*static void	clear_too_long_input(int fd)
{
	char	buff[4096];
	int		size_read;
	char	*newline_pos;

	newline_pos = NULL;
	while (!newline_pos)
	{
		size_read = read(fd, buff, 4096);
		if (size_read == -1)
			exit_error("read() error");
		buff[size_read] = '\0';
		newline_pos = ft_strchr(buff, '\n');
	}
}

char		*ask_for_input(int fd, t_env **env, char **errmsg)
{
	static char	buff[INPUT_MAX_LEN];
	int			size_read;
	char		*ret;
	char		*newline_pos;

	ret = NULL;
	print_prompt(env);
	size_read = read(fd, buff, INPUT_MAX_LEN);
	if (size_read == -1)
		exit_error("read() error");
	buff[size_read] = '\0';
	newline_pos = ft_strchr(buff, '\n');
	if (size_read > 0 && buff[size_read - 1] == '\n')
		buff[size_read - 1] = '\0';
	ret = ft_strdup(buff);
	if (!newline_pos)
	{
		clear_too_long_input(fd);
		free(ret);
		*errmsg = ft_strdup("Command too long.");
		return (NULL);
	}
	return (ret);
}*/

void	clear_cmd(t_termdata *termdata)
{
	while (termdata->cur_row < termdata->max_row)
	{
		ft_putstr(g_shell.termcaps->go_down);
		++termdata->cur_row;
	}
	while (termdata->cur_row >= 0)
	{
		ft_putstr(tgoto(g_shell.termcaps->go_col, 0, 0));
		ft_putstr(g_shell.termcaps->del_line);
		if (termdata->cur_row > 0)
			ft_putstr(g_shell.termcaps->go_up);
		--termdata->cur_row;
	}
	termdata->cur_col = 0;
	termdata->cur_row = 0;
	termdata->max_row = 0;
}

void	print_cmd(char *cmd, t_termdata *termdata)
{
	size_t	i;

	i = 0;
	
	termdata->cur_col = print_prompt(g_shell.env);
	while (cmd[i])
	{
		ft_putchar(cmd[i]);
		if (termdata->cur_col == g_shell.nb_cols - 1)
		{
			ft_putstr(g_shell.termcaps->go_down);
			ft_putstr(tgoto(g_shell.termcaps->go_col, 0, 0));
			termdata->cur_col = 0;
			++termdata->cur_row;
			++termdata->max_row;
		}
		else
			++termdata->cur_col;
		++i;
	}
}

void	add_to_input(char *line, size_t *cur, t_termdata *termdata, char *keybuff)
{
	size_t	i;
	char	tmp;
	char	tmp2;

	clear_cmd(termdata);
	i = *cur;
	tmp = '\0';
	while (line[i]) // if i == INPUT_MAX_LEN => faire gaffe. possible de check avant aussi, genre plus detecter de touches sauf enter quand c'est plein
	{
		tmp2 = line[i];
		line[i] = tmp;
		tmp = tmp2;
		++i;
	}
	line[*cur] = keybuff[0];
	++*cur;
	print_cmd(line, termdata);
}

char	*ask_for_input(t_env **env)
{
	int			read_size;
	size_t		cur;
	t_termdata	termdata;
	static char	keybuff[KEYBUFF_SIZE];
	static char	cmd[INPUT_MAX_LEN];

	(void)env; // yes faut l'enlever
	cur = 0;
	init_termdata(&termdata);
	ft_bzero(keybuff, KEYBUFF_SIZE);
	ft_bzero(cmd, INPUT_MAX_LEN);
	enable_raw_mode();
	print_cmd(cmd, &termdata);
	while ((read_size = read(0, &keybuff, KEYBUFF_SIZE)) != 0)
	{
		if (g_shell.cmd_cancel == 1)
		{
			cur = 0;
			g_shell.cmd_cancel = 0;
			ft_bzero(cmd, INPUT_MAX_LEN);
			termdata.cur_col = print_prompt(env);
		}
		if (read_size == -1)
			exit_error("read() error");
		if (keybuff[0] == '\n')
			break ;
		perform_actions(cmd, &cur, &termdata, keybuff);
		ft_bzero(keybuff, KEYBUFF_SIZE);
	}
	disable_raw_mode();
	ft_putchar('\n');
	return (ft_strdup(cmd));
}
