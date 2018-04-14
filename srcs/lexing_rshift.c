/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_rshift.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:15:05 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/14 12:51:56 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void	lex_rshift_append(t_lexdata *lexdata)
{
	++lexdata->i;
	lexdata->buff[lexdata->j++] = '>';
	lexdata->buff[lexdata->j++] = '>';
}

static void	lex_rshift_classic(t_lexdata *lexdata)
{
	lexdata->buff[lexdata->j++] = '>';
}

void		lex_rshift_word(char *cmdline,
		t_word **wordlist, t_lexdata *lexdata)
{
	lex_shift_src_redirect(cmdline, wordlist, lexdata);
	if (cmdline[lexdata->i + 1] == '>')
		lex_rshift_append(lexdata);
	else
		lex_rshift_classic(lexdata);
	lex_shift_dest_redirect(cmdline, wordlist, lexdata);
	lexdata->buff[lexdata->j] = '\0';
	lexdata->j = 0;
	add_word(lexdata->buff, wordlist);
}
