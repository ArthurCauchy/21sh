/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 11:37:02 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/01 15:44:10 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

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

static void	handle_pipe(t_redirect **redirs, int inputfd, int outputfd)
{
	char	*inputfd_str;
	char	*outputfd_str;

	inputfd_str = ft_itoa(inputfd);
	outputfd_str = ft_itoa(outputfd);
	if (inputfd != 0)
		add_redirect(redirs, "0", inputfd_str, PIPE);
	if (outputfd != 1)
		add_redirect(redirs, "1", outputfd_str, PIPE);
	ft_multifree(2, inputfd_str, outputfd_str);
}

int			exec_ast_arg(t_ast *node, int inputfd, int outputfd)
{
	t_process	*proc;
	char		*errmsg;
	int			ret;

	proc = new_process();
	handle_pipe(&proc->redirs, inputfd, outputfd);
	if (analyze_redirects(&node->arglist, &proc->redirs, &errmsg) == -1)
	{
		print_n_free_errmsg(&errmsg);
		return (1);
	}
	proc->args = ft_memalloc(sizeof(char*) * PARAMS_MAX);
	analyze_arglist(node->arglist, proc->args);
	ret = start_command(g_shell.env, g_shell.env, proc);
	if (g_shell.pipe_lvl > 0)
		--g_shell.pipe_lvl;
	else
		delete_processes(proc);
	return (ret);
}
