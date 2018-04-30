/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 11:37:02 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/30 14:46:33 by acauchy          ###   ########.fr       */
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

static void	exec_ast_arg_init(char ***args, t_redirect **redir_array)
{
	size_t	size;

	size = REDIRECT_MAX * sizeof(t_redirect*);
	ft_bzero(redir_array, size);
	if (!(*args = (char**)malloc((PARAMS_MAX + 1) * sizeof(char*))))
		exit_error("malloc() error");
}

static void	handle_pipe(t_redirect **redir_array, int inputfd, int outputfd)
{
	char	*inputfd_str;
	char	*outputfd_str;

	inputfd_str = ft_itoa(inputfd);
	outputfd_str = ft_itoa(outputfd);
	if (inputfd != 0)
		add_redirect(redir_array, "0", inputfd_str, PIPE);
	if (outputfd != 1)
		add_redirect(redir_array, "1", outputfd_str, PIPE);
	ft_multifree(2, inputfd_str, outputfd_str);
}

int			exec_ast_arg(t_ast *node, int inputfd, int outputfd)
{
	char		*errmsg;
	char		**args;
	int			ret;
	t_redirect	*redir_array[REDIRECT_MAX];

	args = NULL;
	exec_ast_arg_init(&args, redir_array);
	handle_pipe(redir_array, inputfd, outputfd);
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
