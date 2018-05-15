/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 09:42:57 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/15 14:25:35 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int			g_running_proc = -1;

t_process	*create_process(char **args)
{
	t_process   *new;
	
	new = (t_process*)malloc(sizeof(t_process));
	new->next = NULL;
	new->args = args; // copy or not, this is the question
	new->pid = -1;
	completed = 0;
	stopped = 0;
	status = 0;
	return (new);
}

static void delete_args(char **args)
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

t_process	delete_process(t_process *proc)
{
	delete_args(proc->args);
	free(proc);
}

static int	post_process(int status)
{
	if (WIFSIGNALED(status))
	{
		print_sig_error(WTERMSIG(status));
		return (1);
	}
	return (WEXITSTATUS(status));
}

int			start_process(t_env **env, char **args)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		exit_error("fork() error");
	if (pid == 0)
	{
		reset_signals_actions();
		if (execve(args[0], args, env_to_array(env)))
			exit_error("execve() error");
	}
	else
	{
		g_running_proc = pid;
		wait(&status);
		if (status == -1)
			exit_error("wait() error");
		g_running_proc = -1;
		return (post_process(status));
	}
	return (0);
}
