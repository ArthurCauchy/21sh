/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 14:15:05 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/05 09:35:24 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	is_delim(char c)
{
	if (is_separator(c)
			|| c == '/'
			|| c == ';'
			|| c == '|'
			|| c == '>'
			|| c == '<'
			|| c == '~'
			|| c == '$'
			|| c == '\''
			|| c == '"')
		return (1);
	return (0);
}

void		lex_dollar_exp(char *cmdline, t_lexdata *lexdata, char **errmsg)
{
	char	var_name[4096];
	char	*var_value;
	size_t	i;

	var_value = NULL;
	++lexdata->i;
	if (cmdline[lexdata->i] == '$')
	{
		var_value = ft_itoa(g_shell.shell_pgid);
		++lexdata->i;
	}
	else if (cmdline[lexdata->i] == '?')
	{
		var_value = ft_itoa(g_shell.last_command_status);
		++lexdata->i;
	}
	else
	{
		i = 0;
		while (i < 4095 && !is_delim(cmdline[lexdata->i]))
			var_name[i++] = cmdline[lexdata->i++];
		var_name[i] = '\0';
		if (!(var_value = read_from_env(g_shell.env, var_name)))
		{
			*errmsg = ft_strjoin(var_name, ": Undefined variable.");
			return ;
		}
	}
	--lexdata->i;
	i = 0;
	while (i < ft_strlen(var_value))
		lexdata->buff[lexdata->j++] = var_value[i++];
	free(var_value);
}
