/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 09:37:26 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/09 17:22:35 by acauchy          ###   ########.fr       */
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

void	add_to_input(char *line, size_t *cur, char *keybuff)
{
	line[*cur] = keybuff[0];
	++*cur;
	ft_putchar(keybuff[0]);
}

char	*ask_for_input(t_env **env, char **errmsg) // fd useless
{
	int			read_size;
	size_t		cur;
	static char	keybuff[KEYBUFF_SIZE];
	static char	line[INPUT_MAX_LEN];

	(void)errmsg; // still here at the end ? then it's usless
	cur = 0;
	ft_bzero(keybuff, KEYBUFF_SIZE);
	ft_bzero(line, KEYBUFF_SIZE);
	print_prompt(env);
	enable_raw_mode();
	while ((read_size = read(0, &keybuff, KEYBUFF_SIZE)) != 0)
	{
		if (read_size == -1)
			exit_error("read() error");
		if (keybuff[0] == '\n')
			break ;
		perform_actions(line, &cur, keybuff);
		ft_bzero(keybuff, KEYBUFF_SIZE);
	}
	disable_raw_mode();
	ft_putchar('\n');
	return (ft_strdup(line));
}
