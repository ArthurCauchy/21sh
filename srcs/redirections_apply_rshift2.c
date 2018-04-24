/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_apply_rshift2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:29:35 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/24 13:29:36 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	apply_redirect_rshift2(t_redirect *redir)
{
	int	left_fd;
	int	file_fd;

	if (ft_strlen(redir->left) > 0)
		left_fd = ft_atoi(redir->left);
	else
		left_fd = 1;
	file_fd = open_file_fd(redir->right, 1, 1);
	if (file_fd < 0)
		return ;
	dup2(file_fd, left_fd);
}
