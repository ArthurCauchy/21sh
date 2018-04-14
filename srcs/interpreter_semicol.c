/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_semicol.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 11:37:43 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/13 11:26:01 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int	exec_ast_semicol(t_ast *node, int inputfd, int outputfd)
{
	int	ret;

	exec_ast(node->left, inputfd, outputfd);
	ret = exec_ast(node->right, inputfd, outputfd);
	return (ret);
}
