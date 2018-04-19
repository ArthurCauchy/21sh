/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 10:59:12 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/19 23:40:07 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static char	*extract_left_digits(char *str)
{
	char	buff[64];
	size_t	i;
	
	ft_strncpy(buff, str, 64);
	i = 0;
	while (i < 64)
	{
		if (!ft_isdigit(buff[i]))
		{
			buff[i] = '\0';
			break;
		}
		++i;
	}
	return (ft_strdup(buff));
}

void		add_redirect(t_redirect **redir_array, char *left, char *right, t_token token)
{
	t_redirect	*redirect;
	size_t		i;

	redirect = new_redirect(left, right, token);
	i = 0;
	while (i < REDIRECT_MAX && redir_array[i] != NULL)
		++i;
	redir_array[i] = redirect;
}

int			analyze_redirects(t_word **arglist, t_redirect **redir_array, char **errmsg)
{
	t_word	*cur;
	t_word	*next;
	char	*left;

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
			left = extract_left_digits(cur->str);
			add_redirect(redir_array, left, next->str, cur->token);
			free(left);
			remove_word(arglist, cur);
			remove_word(arglist, next);
			cur = *arglist;
		}
		else
			cur = cur->next;
	}
	return (0);
}
