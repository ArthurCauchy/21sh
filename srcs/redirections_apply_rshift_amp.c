/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_apply_rshift_amp.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:30:48 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/30 14:17:09 by acauchy          ###   ########.fr       */
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

int			apply_redirect_rshift_amp(t_redirect *redir,
		int *fdsave_array, char **errmsg)
{
	int	left_fd;
	int	right_fd;

	if (ft_strlen(redir->left) > 0)
		left_fd = ft_atoi(redir->left);
	else
		left_fd = 1;
	if (!is_numerical(redir->right))
	{
		if (strcmp(redir->right, "-") == 0)
		{
			save_filedes(fdsave_array, left_fd);
			close(left_fd);
			return (0);
		}
		*errmsg = ft_strjoin(redir->right, ": Not a file descriptor !");
		return (-1);
	}
	right_fd = ft_atoi(redir->right);
	save_filedes(fdsave_array, left_fd);
	dup2(right_fd, left_fd);
	return (0);
}
