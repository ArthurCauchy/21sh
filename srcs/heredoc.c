/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 11:00:26 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/26 15:19:16 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int			open_heredoc_file(char *filename, char **errmsg)
{
	int flags;
	int fd;

	flags = O_WRONLY | O_CREAT | O_EXCL | O_TRUNC;
	fd = open(filename, flags, 0600);
	if (fd < 0)
	{
		*errmsg = ft_strdup(filename);
		*errmsg = ft_strjoin_free(*errmsg, ft_strdup(": "));
		*errmsg = ft_strjoin_free(*errmsg, ft_strdup(strerror(errno)));
	}
	return (fd);
}

void		write_heredoc_line(char *line, int fd)
{
	static char	buff[4096];
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (j < 4095)
			buff[j++] = line[i];
		else
		{
			buff[j++] = '\n';
			write(fd, buff, j);
			j = 0;
		}
		++i;
	}
	buff[j++] = '\n';
	write(fd, buff, j);
	j = 0;
}

static int	write_heredoc(int fd, char *end_delim)
{
	char	*line;

	while ((line = ask_for_heredoc()))
	{
		if (ft_strcmp(end_delim, line) == 0)
			break ;
		write_heredoc_line(line, fd);
		free(line);
	}
	if (!line)
		return (-1);
	free(line);
	return (0);
}

static int	ask_input_heredoc(t_word *wordlist, char **errmsg)
{
	int	heredoc_fd;

	heredoc_fd = open_heredoc_file("/tmp/heredoc-tmp", errmsg);
	if (heredoc_fd == -1)
		return (-1);
	if (write_heredoc(heredoc_fd, wordlist->next->str) == -1)
	{
		close(heredoc_fd);
		unlink("/tmp/heredoc-tmp");
		return (-1);
	}
	close(heredoc_fd);
	return (0);
}

int			apply_heredocs(t_word *wordlist, char **errmsg)
{
	int	heredoc_fd;

	while (wordlist)
	{
		if (wordlist->token == LSHIFT2)
		{
			if (!wordlist->next || wordlist->next->token != ARG)
			{
				*errmsg = ft_strdup("Missing name for redirect.");
				return (-1);
			}
			if (ask_input_heredoc(wordlist, errmsg) == -1)
				return (-1);
			heredoc_fd = open_file_fd("/tmp/heredoc-tmp", 0, 0, errmsg);
			if (heredoc_fd == -1)
				return (-1);
			unlink("/tmp/heredoc-tmp");
			free(wordlist->next->str);
			register_heredoc_fd(heredoc_fd);
			wordlist->next->str = ft_itoa(heredoc_fd);
		}
		wordlist = wordlist->next;
	}
	return (0);
}
