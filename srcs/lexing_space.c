/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:15:05 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/02 20:16:40 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	lex_space_word(char *cmdline, t_word **wordlist,
		t_lexdata *lexdata, char **errmsg)
{
	(void)errmsg;
	lexdata->buff[lexdata->j] = '\0';
	lexdata->j = 0;
	if (ft_strlen(lexdata->buff) > 0)
		add_word(ARG, lexdata->buff, wordlist);
	while (lexdata->i <= ft_strlen(cmdline)
			&& is_separator(cmdline[lexdata->i]))
		++lexdata->i;
	--lexdata->i;
}
