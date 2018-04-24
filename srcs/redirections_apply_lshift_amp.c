/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_apply_lshift_amp.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:29:23 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/24 13:29:24 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	is_numerical(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		++str;
	}
	return (1);
}

void		apply_redirect_lshift_amp(t_redirect *redir)
{
	int	left_fd;
	int	right_fd;

	left_fd = ft_atoi(redir->left);
	if (!is_numerical(redir->right))
	{
		if (strcmp(redir->right, "-") == 0)
			close(left_fd);
		return ;
	}
	right_fd = ft_atoi(redir->right);
	dup2(right_fd, left_fd);
}
