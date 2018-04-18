/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_parse_semicol.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 13:53:02 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/18 12:22:07 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		parse_semicol(t_word **symbol, t_ast **current)
{
	t_ast	*semicol;

	parse_or(symbol, current);
	while (*symbol && (*symbol)->token == SEMICOL)
	{
		semicol = new_ast_node(SEMICOL, NULL);
		semicol->left = *current;
		parse_or(symbol, current);
		semicol->right = *current;
		*current = semicol;
	}
}
