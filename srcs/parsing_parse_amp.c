/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_parse_amp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 13:53:02 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/16 13:37:16 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void		parse_amp(t_word **symbol, t_ast **current)
{
	t_ast	*amp;

	parse_semicol(symbol, current);
	while (*symbol && (*symbol)->token == AMP)
	{
		amp = new_ast_node(AMP, NULL);
		amp->left = *current;
		parse_semicol(symbol, current);
		amp->right = *current;
		*current = amp;
	}
}
