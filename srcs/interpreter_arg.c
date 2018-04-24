/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 11:37:02 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/24 14:03:12 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void	delete_args(char **args)
{
	size_t	i;

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
	t_redirect	*redir_array[REDIRECT_MAX];

	ft_bzero(redir_array, REDIRECT_MAX);
	if (!(args = (char**)malloc((PARAMS_MAX + 1) * sizeof(char*))))
		exit_error("malloc() error");
	if (inputfd != 0)
		add_redirect(redir_array, "0", ft_itoa(inputfd), PIPE);
	if (outputfd != 1)
		add_redirect(redir_array, "1", ft_itoa(outputfd), PIPE);
	if (analyze_redirects(&node->arglist, redir_array, &errmsg) == -1)
	{
		print_n_free_errmsg(&errmsg);
		delete_redir_array(redir_array);
		return (1);
	}
	analyze_arglist(node->arglist, args);
	ret = start_command(g_envptr, g_envptr, args, redir_array);
	delete_args(args);
	delete_redir_array(redir_array);
	return (ret);
}
