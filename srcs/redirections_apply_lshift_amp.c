/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_apply_lshift_amp.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:29:23 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/26 15:46:55 by arthur           ###   ########.fr       */
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

int			apply_redirect_lshift_amp(t_redirect *redir, int *fdsave_array, char **errmsg)
{
	int	left_fd;
	int	right_fd;

	left_fd = ft_atoi(redir->left);
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
