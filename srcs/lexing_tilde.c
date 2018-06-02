/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:15:05 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/02 20:58:11 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	lex_tilde_exp(char *cmdline, t_lexdata *lexdata, char **errmsg)
{
	char	*home;
	size_t	i;

	(void)cmdline;
	if (!(home = read_from_env(g_shell.env, "HOME")))
	{
		*errmsg = ft_strdup("No $HOME variable set.");
		return ;
	}
	i = 0;
	while (i < ft_strlen(home))
		lexdata->buff[lexdata->j++] = home[i++];
	free(home);
}
