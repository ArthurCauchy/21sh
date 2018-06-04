/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_apply.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:29:12 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/04 09:45:33 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

/*
** mode :
** 0) read
** 1) write
*/

int	open_file_fd(char *filename, int mode, int append, char **errmsg)
{
	int flags;
	int fd;

	if (mode == 0)
		flags = O_RDONLY;
	else
	{
		flags = O_WRONLY | O_CREAT;
		if (append == 1)
			flags = flags | O_APPEND;
		else
			flags = flags | O_TRUNC;
	}
	fd = open(filename, flags, 0644);
	if (fd < 0)
	{
		*errmsg = ft_strdup(filename);
		*errmsg = ft_strjoin_free(*errmsg, ft_strdup(": "));
		*errmsg = ft_strjoin_free(*errmsg, ft_strdup(strerror(errno)));
	}
	return (fd);
}

int	apply_redirects(t_redirect *redirs, int *fdtmp_array, int *fdsave_array, char **errmsg)
{
	t_redirect	*cur;
	int			ret;

	cur = redirs;
	while (cur)
	{
		if (cur->token == PIPE)
			ret = apply_redirect_pipe(cur, fdtmp_array, fdsave_array, errmsg);
		if (cur->token == PIPECLOSE)
		{
			//ft_atoi(cur->right);
			// close cur->right
			ret = 0;
		}
		else if (cur->token == LSHIFT)
			ret = apply_redirect_lshift(cur, fdtmp_array, fdsave_array, errmsg);
		else if (cur->token == LSHIFT_AMP)
			ret = apply_redirect_lshift_amp(cur, fdtmp_array, fdsave_array, errmsg);
		else if (cur->token == RSHIFT)
			ret = apply_redirect_rshift(cur, fdtmp_array, fdsave_array, errmsg);
		else if (cur->token == RSHIFT_AMP)
			ret = apply_redirect_rshift_amp(cur, fdtmp_array, fdsave_array, errmsg);
		else if (cur->token == RSHIFT2)
			ret = apply_redirect_rshift2(cur, fdtmp_array, fdsave_array, errmsg);
		if (ret == -1)
			return (-1);
		cur = cur->next;
	}
	return (0);
}
