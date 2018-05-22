/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 11:16:48 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/22 11:52:25 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	is_valid_job(t_ast *node)
{
	if (!node)
		return (0);
	if (node->token == ARG && node->arglist != NULL)
		return (1);
	else if (node->left)
		return (is_valid_job(node->left));
	else if (node->right)
		return (is_valid_job(node->right));
	else
		return (0);
}

static void	add_job(t_ast *subtree, t_job **jobs, int bg)
{
	t_job	*cur;
	t_job	*new;

	new = create_job();
	new->arg_tree = copy_ast(subtree);
	new->is_background = bg;
	cur = *jobs;
	if (!cur)
		*jobs = new;
	else
	{
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}

/*
** return : 1 = AMP in self or subtree, 0 = no AMP
*/
static int	split_jobs_recur(t_ast *node, t_job **jobs, int bg)
{
	int			ret1;
	int			ret2;

	ret1 = 0;
	ret2 = 0;
	if (node->left)
	{
		ret1 = split_jobs_recur(node->left, jobs, 1);
		if (ret1 == 0 && node->token == AMP && is_valid_job(node->left))
			add_job(node->left, jobs, 1);
	}
	if (node->right)
	{
		ret2 = split_jobs_recur(node->right, jobs, bg);
		if (ret2 == 0 && node->token == AMP && is_valid_job(node->right))
			add_job(node->right, jobs, bg);
	}
	if (ret1 == 1 || ret2 == 1 || node->token == AMP)
		return (1);
	return (0);
}

void split_jobs(t_ast *node, t_job **jobs)
{
	t_ast	*new;

	new = new_ast_node(AMP, NULL);
	new->right = node;
	split_jobs_recur(new, jobs, 0);
}
