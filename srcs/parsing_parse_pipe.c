/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_parse_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 13:53:02 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/14 12:50:42 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		parse_pipe(t_word **symbol, t_ast **current)
{
	t_ast	*pipe;

	parse_arg(symbol, current);
	while (*symbol && ft_strcmp((*symbol)->str, "|") == 0)
	{
		pipe = new_ast_node(PIPE, NULL);
		pipe->left = *current;
		parse_arg(symbol, current);
		pipe->right = *current;
		*current = pipe;
	}
}
