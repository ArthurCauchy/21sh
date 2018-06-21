/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 11:00:26 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/21 18:22:03 by arthur           ###   ########.fr       */
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


void	write_heredoc(int fd, char *end_delim)
{
	char	*line;

	while (ft_strcmp(end_delim, line = ask_for_heredoc()) != 0)
	{
		write_heredoc_line(line, fd);
		free(line);
	}
}
