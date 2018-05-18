/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 10:29:04 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/18 12:31:57 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

t_ast			*new_ast_node(t_token token, t_word *arglist)
{
	t_ast	*node;

	if (!(node = (t_ast*)malloc(sizeof(t_ast))))
		exit_error("malloc() error");
	node->token = token;
	if (arglist)
		node->arglist = new_word(arglist->token, arglist->str);
	else
		node->arglist = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

static void		delete_ast_node(t_ast *node)
{
	if (!node)
		return ;
	delete_ast_node(node->left);
	delete_ast_node(node->right);
	delete_wordlist(&node->arglist);
	free(node);
}

void			delete_ast(t_ast **ast)
{
	delete_ast_node(*ast);
	*ast = NULL;
}

t_ast			*copy_node(t_ast *src)
{
	t_ast	*dest;

	if (!src)
		return (NULL);
	dest = (t_ast*)malloc(sizeof(t_ast));
	dest->token = src->token;
	dest->arglist = copy_wordlist(src->arglist);
	dest->left = NULL;
	dest->right = NULL;
	return (dest);
}

t_ast			*copy_ast(t_ast *src)
{
	t_ast	*dest;

	if (!src)
		return (NULL);
	dest = copy_node(src);
	dest->left = copy_ast(src->left);
	dest->right = copy_ast(src->right);
	return (dest);
}
