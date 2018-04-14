/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_parse_arg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 13:53:02 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/14 12:50:53 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int	is_token(char *str)
{
	if (ft_strcmp(str, ";") == 0
			|| ft_strcmp(str, "||") == 0
			|| ft_strcmp(str, "&&") == 0
			|| ft_strcmp(str, "|") == 0)
		return (1);
	return (0);
}

void		parse_arg(t_word **symbol, t_ast **current)
{
	t_word	*cur;
	t_ast	*curr_arg;

	curr_arg = NULL;
	*symbol = (*symbol)->next;
	if (!*symbol || is_token((*symbol)->str))
		*current = new_ast_node(ARG, NULL);
	while (*symbol && !is_token((*symbol)->str))
	{
		if (curr_arg)
		{
			cur = curr_arg->arglist;
			while (cur->next)
				cur = cur->next;
			cur->next = new_word((*symbol)->str);
		}
		else
		{
			curr_arg = new_ast_node(ARG, *symbol);
			*current = curr_arg;
		}
		*symbol = (*symbol)->next;
	}
}
