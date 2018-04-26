/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_apply.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:29:12 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/26 15:45:40 by arthur           ###   ########.fr       */
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

	if (append)
		flags = O_CREAT | O_APPEND;
	else
		flags = O_CREAT;
	if (mode == 0)
		flags = flags | O_RDONLY;
	else if (mode == 1)
		flags = flags | O_WRONLY;
	fd = open(filename, flags, 0644);
	if (fd < 0)
	{
		*errmsg = ft_strdup(filename);
		*errmsg = ft_strjoin_free(*errmsg, ft_strdup(": "));
		*errmsg = ft_strjoin_free(*errmsg, ft_strdup(strerror(errno)));
	}
	return (fd);
}

int	apply_redirects(t_redirect **redir_array, int *fdsave_array, char **errmsg)
{
	size_t	i;
	int		ret;

	i = 0;
	while (i < REDIRECT_MAX && redir_array[i] != NULL)
	{
		if (redir_array[i]->token == PIPE)
			ret = apply_redirect_pipe(redir_array[i], fdsave_array, errmsg);
		else if (redir_array[i]->token == LSHIFT)
			ret = apply_redirect_lshift(redir_array[i], fdsave_array, errmsg);
		else if (redir_array[i]->token == LSHIFT_AMP)
			ret = apply_redirect_lshift_amp(redir_array[i], fdsave_array, errmsg);
		else if (redir_array[i]->token == RSHIFT)
			ret = apply_redirect_rshift(redir_array[i], fdsave_array, errmsg);
		else if (redir_array[i]->token == RSHIFT_AMP)
			ret = apply_redirect_rshift_amp(redir_array[i], fdsave_array, errmsg);
		else if (redir_array[i]->token == RSHIFT2)
			ret = apply_redirect_rshift2(redir_array[i], fdsave_array, errmsg);
		if (ret == -1)
			return (-1);
		++i;
	}
	return (0);
}
