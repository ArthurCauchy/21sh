/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_semicol.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 11:37:43 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/16 14:20:11 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	interpret_semicol(t_ast *node)
{
	interpret_ast(node->left);
	interpret_ast(node->right);
}
