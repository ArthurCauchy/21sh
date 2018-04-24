/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_validator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 10:15:47 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/17 12:05:24 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	is_null_node(t_ast *node)
{
	return (node->token == ARG && node->arglist == NULL);
}

static int	validate_node(t_ast *node, char **errmsg)
{
	if (node->token == PIPE &&
			(is_null_node(node->left) || is_null_node(node->right)))
	{
		*errmsg = ft_strdup("Invalid null command.");
		return (1);
	}
	if (node->token == AND && is_null_node(node->right))
	{
		*errmsg = ft_strdup("Invalid null command.");
		return (1);
	}
	if (node->token == OR &&
			(is_null_node(node->left) || is_null_node(node->right)))
	{
		*errmsg = ft_strdup("Invalid null command.");
		return (1);
	}
	return (0);
}

int			validate_ast(t_ast *root, char **errmsg)
{
	if (!root)
		return (0);
	if (validate_ast(root->left, errmsg) != 0
			|| validate_node(root, errmsg) != 0
			|| validate_ast(root->right, errmsg))
		return (1);
	return (0);
}
