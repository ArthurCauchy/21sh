/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starter_jobs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 11:37:12 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/15 14:58:24 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	start_job(t_env **env, t_job *j, int foreground)
{
	t_process	*p;
	pid_t		pid;
	int			mypipe[2];
	int			infile;
	int			outfile;

	infile = j->stdin;
	p = j->first_process;
	while (p)
	{
		/* Set up pipes, if necessary.  */
		if (p->next)
		{
			if (pipe(mypipe) < 0)
				exit_error("pipe() error");
			outfile = mypipe[1];
		}
		else
			outfile = j->stdout;
		/* Fork the child processes.  */
		if ((pid = fork ()) == -1)
			exit_error("fork() error");
		else if (pid == 0)
		{
			/* This is the child process.  */
			//launch_process(p, j->pgid, infile, outfile, j->stderr, foreground);
			start_command(env, env, p->args, NULL);
		}
		else
		{
			/* This is the parent process.  */
			p->pid = pid;
			if (g_shell.is_interactive)
			{
				if (!j->pgid)
					j->pgid = pid;
				setpgid(pid, j->pgid);
			}
		}
		/* Clean up after pipes.  */
		if (infile != j->stdin)
			close(infile);
		if (outfile != j->stdout)
			close(outfile);
		infile = mypipe[0];
		p = p->next;
	}
	//format_job_info(j, "launched");
	if (!g_shell.is_interactive)
		wait_for_job(j);
	else if (foreground)
		put_job_in_foreground(j, 0);
	else
		put_job_in_background(j, 0);
}
