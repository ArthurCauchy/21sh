/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 10:59:12 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/18 15:21:04 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int	open_file_fd(char *filename, int append)
{
	int	flags;
	int	fd;

	if (append)
		flags = O_CREAT | O_APPEND;
	else
		flags = O_CREAT;
	fd = open(filename, flags, 0644);
	return (fd);
}

int			analyze_redirects(t_word *arglist, char **errmsg)
{
	t_word	*cur;
	t_word	*next;
	int		tmp_fd;

	cur = arglist;
	while (cur)
	{
		if (/*cur->token == LSHIFT
				|| cur->token == LSHIFT2
				||*/ cur->token == RSHIFT
				|| cur->token == RSHIFT2)
		{
			next = cur->next;
			if (!next || next->token != ARG)
			{
				*errmsg = ft_strdup("Missing name for redirect.");
				return (-1);
			}
			tmp_fd = open_file_fd(next->str, cur->token == RSHIFT2);
			cur = cur->next;
		}
		if (cur)
			cur = cur->next;
	}
	return (0);
}
