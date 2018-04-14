/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 11:37:02 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/13 11:57:58 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int	exec_ast_arg(t_ast *node, int inputfd, int outputfd)
{
	t_word	*cur;

	(void)inputfd;
	(void)outputfd;
	cur = node->arglist;
	ft_putstr("exec : ");
	while (cur)
	{
		ft_putstr(cur->str);
		if (cur->next)
			ft_putchar(' ');
		cur = cur->next;
	}
	ft_putchar('\n');
	return (0);
}
