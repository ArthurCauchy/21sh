/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 11:37:02 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/19 16:02:40 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void	delete_args(char **args)
{
	size_t  i;
	
	i = 0;
	while (args[i])
	{
		free(args[i]);
		++i;
	}
	free(args);
}

static void	analyze_arglist(t_word *arglist, char **args)
{
	t_word	*cur;
	size_t	i;

	cur = arglist;
	i = 0;
	while (i < PARAMS_MAX && cur)
	{
			args[i] = ft_strdup(cur->str); 
			++i;
			cur = cur->next;
	}
	args[i] = NULL;
}

int			exec_ast_arg(t_ast *node, int inputfd, int outputfd)
{
	char		*errmsg;
	char		**args;
	int			ret;
	t_redirect	*redir_array[65536];

	ft_bzero(redir_array, sizeof(redir_array));
	if (!(args = (char**)malloc((PARAMS_MAX + 1) * sizeof(char*))))
		exit_error("malloc() error");
	if (analyze_redirects(&node->arglist, redir_array, &errmsg) == -1)
	{
		print_n_free_errmsg(&errmsg);
		return (1);
	}
	analyze_arglist(node->arglist, args);
	ret = start_command(g_envptr, g_envptr, args, inputfd, outputfd);
	delete_args(args);
	return (ret);
}
