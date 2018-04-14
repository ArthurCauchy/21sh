/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 13:56:56 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/13 10:57:10 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int				main(void)
{
	char	buff[4096];
	int		size_read;
	t_word	*wordlist;
	t_ast	*ast;
	t_word	*cur;
	int		retcode;
	char	*tmp;

	wordlist = NULL;
	ast = NULL;
	while ((size_read = read(0, buff, 4095)))
	{
		buff[size_read] = '\0';
		if (buff[size_read - 1] == '\n')
			buff[size_read - 1] = '\0';
		if (ft_strlen(buff) == 0)
			break;
		lex_analysis(buff, &wordlist);
		cur = wordlist;
		while (cur)
		{
			ft_fminiprint(1, "\"%l0s%\"\n", cur->str);
			cur = cur->next;
		}
		ft_putstr("\n\n");
		syntax_analysis(&wordlist, &ast);
		delete_wordlist(&wordlist);
		ft_putstr("\n\n");
		retcode = validate_ast(ast);
		if (retcode != 0)
		{
			tmp = code_to_errmessage(retcode);
			ft_putendl_fd(tmp, 2);
			free(tmp);
			delete_ast(&ast);
			continue;
		}
		exec_ast(ast, 0, 1);
		delete_ast(&ast);
	}
	return (0);
}
