/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_or.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 11:36:55 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/04 09:07:42 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int	exec_ast_or(t_ast *node, int *pipein, int *pipeout)
{
	int	ret1;
	int	ret2;

	ret1 = exec_ast(node->left, pipein, pipeout);
	if (ret1 != 0)
	{
		ret2 = exec_ast(node->right, pipein, pipeout);
		return (ret2);
	}
	return (0);
}
