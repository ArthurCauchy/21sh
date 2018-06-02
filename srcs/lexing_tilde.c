/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:15:05 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/02 17:33:01 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	lex_tilde_exp(char *cmdline,
		t_word **wordlist, t_lexdata *lexdata)
{
	char	*home;
	size_t	i;

	if (!(home = read_from_env(g_shell.env, "HOME")))
		home = ft_strdup(""); // this is temporary - ERROR INSTEAD !
	(void)wordlist;
	(void)cmdline;
	/*lexdata->buff[lexdata->j] = '\0';
	lexdata->j = 0;
	if (ft_strlen(lexdata->buff) > 0)
		add_word(ARG, lexdata->buff, wordlist);
	add_word(SEMICOL, ";", wordlist);*/
	i = 0;
	while (i < ft_strlen(home))
		lexdata->buff[lexdata->j++] = home[i++];
}
