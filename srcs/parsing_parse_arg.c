/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_parse_arg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 13:53:02 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/18 12:33:19 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	is_tree_token(t_word *word)
{
	if (word->token == SEMICOL
			|| word->token == OR
			|| word->token == AND
			|| word->token == PIPE)
		return (1);
	return (0);
}

void		parse_arg(t_word **symbol, t_ast **current)
{
	t_word	*cur;
	t_ast	*curr_arg;

	curr_arg = NULL;
	*symbol = (*symbol)->next;
	if (!*symbol || is_tree_token(*symbol))
		*current = new_ast_node(ARG, NULL);
	while (*symbol && !is_tree_token(*symbol))
	{
		if (curr_arg)
		{
			cur = curr_arg->arglist;
			while (cur->next)
				cur = cur->next;
			cur->next = new_word((*symbol)->token, (*symbol)->str);
		}
		else
		{
			curr_arg = new_ast_node(ARG, *symbol);
			*current = curr_arg;
		}
		*symbol = (*symbol)->next;
	}
}
