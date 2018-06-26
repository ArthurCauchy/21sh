/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 11:37:02 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/26 11:38:46 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void	handle_pipe(t_redirect **redirs, int *pipein, int *pipeout)
{
	char	*tmp_str;

	if (pipein != NULL)
	{
		tmp_str = ft_itoa(pipein[0]);
		add_redirect(redirs, "0", tmp_str, PIPE);
		free(tmp_str);
	}
	if (pipeout != NULL)
	{
		tmp_str = ft_itoa(pipeout[1]);
		add_redirect(redirs, "1", tmp_str, PIPE);
		free(tmp_str);
		tmp_str = ft_itoa(pipeout[0]);
		add_redirect(redirs, "", tmp_str, FDCLOSE);
		free(tmp_str);
	}
}

int			exec_ast_arg(t_ast *node, int *pipein, int *pipeout)
{
	t_process	*proc;
	char		*errmsg;
	int			ret;

	proc = new_process();
	handle_pipe(&proc->redirs, pipein, pipeout);
	if (analyze_redirects(&node->arglist, &proc->redirs, &errmsg) == -1)
	{
		print_n_free_errmsg(&errmsg);
		ret = 1;
	}
	else
	{
		proc->args = ft_memalloc(sizeof(char*) * PARAMS_MAX);
		analyze_arglist(node->arglist, proc->args);
		ret = start_command(g_shell.env, g_shell.env, proc);
	}
	if (g_shell.pipe_lvl > 0)
		--g_shell.pipe_lvl;
	delete_processes(proc);
	return (ret);
}
