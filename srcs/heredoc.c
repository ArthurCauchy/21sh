/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 11:00:26 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/22 12:03:39 by acauchy          ###   ########.fr       */
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


void	write_heredoc_line(char *line, int fd)
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


static void	write_heredoc(int fd, char *end_delim)
{
	char	*line;

	while (ft_strcmp(end_delim, line = ask_for_heredoc()) != 0)
	{
		write_heredoc_line(line, fd);
		free(line);
	}
	free(line);
}

void		apply_heredocs(t_word *wordlist, char **errmsg)
{
	int	heredoc_fd;

	while (wordlist)
	{
		if (wordlist->token == LSHIFT2)
		{
			if (!wordlist->next || wordlist->next->token != ARG)
			{
				*errmsg = ft_strdup("Missing name for redirect.");
				return ;
			}
			heredoc_fd = open_heredoc_file("/tmp/heredoc-tmp", errmsg);
			if (heredoc_fd == -1)
				return ;
			write_heredoc(heredoc_fd, wordlist->next->str);
			close(heredoc_fd);
			heredoc_fd = open_file_fd("/tmp/heredoc-tmp", 0, 0, errmsg);
			if (heredoc_fd == -1)
				return ;
			unlink("/tmp/heredoc-tmp");
			free(wordlist->next->str);
			register_heredoc_fd(heredoc_fd);
			wordlist->next->str = ft_itoa(heredoc_fd);
		}
		wordlist = wordlist->next;
	}
}
