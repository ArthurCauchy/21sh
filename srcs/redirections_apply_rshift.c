/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_apply_rshift.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:29:29 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/30 14:20:05 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int	apply_redirect_rshift(t_redirect *redir, int *fdsave_array, char **errmsg)
{
	int	left_fd;
	int	file_fd;

	if (ft_strlen(redir->left) > 0)
		left_fd = ft_atoi(redir->left);
	else
		left_fd = 1;
	file_fd = open_file_fd(redir->right, 1, 0, errmsg);
	if (file_fd < 0)
		return (-1);
	save_filedes(fdsave_array, left_fd);
	dup2(file_fd, left_fd);
	close(file_fd);
	return (0);
}
