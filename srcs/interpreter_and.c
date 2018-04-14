/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_and.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 11:36:50 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/13 11:26:28 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int	exec_ast_and(t_ast *node, int inputfd, int outputfd)
{
	int	ret1;
	int	ret2;

	ret1 = exec_ast(node->left, inputfd, outputfd);
	if (ret1 == 0)
	{
		ret2 = exec_ast(node->right, inputfd, outputfd);
		return (ret2);
	}
	return (ret1);
}
