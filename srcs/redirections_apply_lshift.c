/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_apply_lshift.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:29:17 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/30 14:20:22 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int	apply_redirect_lshift(t_redirect *redir, int *fdsave_array, char **errmsg)
{
	int	left_fd;
	int	file_fd;

	left_fd = ft_atoi(redir->left);
	file_fd = open_file_fd(redir->right, 0, 0, errmsg);
	if (file_fd < 0)
		return (-1);
	save_filedes(fdsave_array, left_fd);
	dup2(file_fd, left_fd);
	close(file_fd);
	return (0);
}
