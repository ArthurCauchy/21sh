/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 13:53:02 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/18 12:18:48 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void		build_tree(t_word **wordlist, t_ast **root)
{
	t_word	*start_word;
	t_word	*symbol;

	symbol = *wordlist;
	start_word = new_word(ARG, "");
	start_word->next = symbol;
	symbol = start_word;
	parse_semicol(&symbol, root);
	free(start_word->str);
	free(start_word);
}

void			syntax_analysis(t_word **wordlist, t_ast **root)
{
	build_tree(wordlist, root);
}
