/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_apply_lshift2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:29:35 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/20 12:10:10 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int	apply_redirect_lshift2(t_redirect *redir, int *fdtmp_array, int *fdsave_array, char **errmsg)
{
	int	left_fd;
	int	heredoc_fd;
	int	file_fd;

	left_fd = ft_atoi(redir->left);
	heredoc_fd = open_heredoc_file("/tmp/heredoc-tmp", errmsg);
	if (heredoc_fd == -1)
		return (-1);
	write(heredoc_fd, "heredoc test", 12);
	close(heredoc_fd);
	file_fd = open_file_fd("/tmp/heredoc-tmp", 0, 0, errmsg);
	unlink("/tmp/heredoc-tmp");
	if (file_fd < 0)
		return (-1);
	if (fdtmp_array && fdsave_array)
		save_filedes(fdtmp_array, fdsave_array, left_fd);
	if (dup2(file_fd, left_fd) == -1)
		*errmsg = ft_strjoin("21sh: ", strerror(errno));
	close(file_fd);
	return (!*errmsg ? 0 : -1);
}
