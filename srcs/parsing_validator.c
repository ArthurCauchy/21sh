/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_validator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 10:15:47 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/14 12:51:13 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char		*code_to_errmessage(int code)
{
	if (code == 1)
		return (ft_strdup("Invalid null command."));
	else
		return (NULL);
}

static int	is_null_node(t_ast *node)
{
	return (node->token == ARG && node->arglist == NULL);
}

static int	validate_node(t_ast *node)
{
	if (node->token == PIPE &&
			(is_null_node(node->left) || is_null_node(node->right)))
		return (1);
	if (node->token == AND && is_null_node(node->right))
		return (1);
	if (node->token == OR &&
			(is_null_node(node->left) || is_null_node(node->right)))
		return (1);
	return (0);
}

int			validate_ast(t_ast *root)
{
	int	tmpcode;

	if (!root)
		return (0);
	tmpcode = validate_ast(root->left);
	if (tmpcode != 0)
		return (tmpcode);
	tmpcode = validate_node(root);
	if (tmpcode != 0)
		return (tmpcode);
	tmpcode = validate_ast(root->right);
	if (tmpcode != 0)
		return (tmpcode);
	return (0);
}
