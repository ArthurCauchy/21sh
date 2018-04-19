/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 10:59:12 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/19 15:58:44 by arthur           ###   ########.fr       */
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

static void	add_redirect(t_redirect **redir_array, t_word *word, t_word *nextword)
{
	t_redirect	*redirect;
	int			in_fd;
	int			out_fd;
	size_t		i;

	in_fd = atoi(word->str);
	if (!ft_isdigit(word->str[0]) && (word->token == RSHIFT || word->token == RSHIFT2))
		in_fd = 1;
	if (ft_strchr(word->str, '&'))
		out_fd = open_file_fd(nextword->str, word->token == RSHIFT2);
	else
		out_fd = atoi(nextword->str);
	redirect = new_redirect(in_fd, out_fd, word->token == LSHIFT);
	i = 0;
	while (i < sizeof(redir_array) / sizeof(redir_array[0]) && redir_array[i] != NULL)
		++i;
	redir_array[i] = redirect;
}

int			analyze_redirects(t_word **arglist, t_redirect **redir_array, char **errmsg)
{
	t_word	*cur;
	t_word	*next;

	cur = *arglist;
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
			add_redirect(redir_array, cur, next);
			remove_word(arglist, cur);
			remove_word(arglist, next);
			cur = *arglist;
		}
		else
			cur = cur->next;
	}
	return (0);
}
