/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_lshift.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:15:05 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/14 12:52:06 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void	lex_lshift_append(char *cmdline,
		t_word **wordlist, t_lexdata *lexdata)
{
	(void)cmdline;
	++lexdata->i;
	add_word("<<", wordlist);
}

static void	lex_lshift_classic(char *cmdline,
		t_word **wordlist, t_lexdata *lexdata)
{
	(void)cmdline;
	(void)lexdata;
	add_word("<", wordlist);
}

void		lex_lshift_word(char *cmdline,
		t_word **wordlist, t_lexdata *lexdata)
{
	lexdata->buff[lexdata->j] = '\0';
	lexdata->j = 0;
	if (ft_strlen(lexdata->buff) > 0)
		add_word(lexdata->buff, wordlist);
	if (cmdline[lexdata->i + 1] == '<')
		lex_lshift_append(cmdline, wordlist, lexdata);
	else
		lex_lshift_classic(cmdline, wordlist, lexdata);
}
