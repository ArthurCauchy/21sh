/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_rshift.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:15:05 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/18 12:16:07 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void	lex_rshift_append(t_lexdata *lexdata, t_token *token)
{
	*token = RSHIFT2;
	++lexdata->i;
	lexdata->buff[lexdata->j++] = '>';
	lexdata->buff[lexdata->j++] = '>';
}

static void	lex_rshift_classic(t_lexdata *lexdata, t_token *token)
{
	*token = RSHIFT;
	lexdata->buff[lexdata->j++] = '>';
}

void		lex_rshift_word(char *cmdline,
		t_word **wordlist, t_lexdata *lexdata)
{
	t_token token;

	lex_shift_src_redirect(cmdline, wordlist, lexdata);
	if (cmdline[lexdata->i + 1] == '>')
		lex_rshift_append(lexdata, &token);
	else
		lex_rshift_classic(lexdata, &token);
	lex_shift_dest_redirect(cmdline, wordlist, lexdata);
	lexdata->buff[lexdata->j] = '\0';
	lexdata->j = 0;
	add_word(token, lexdata->buff, wordlist);
}
