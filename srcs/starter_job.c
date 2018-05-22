/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starter_job.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 11:37:12 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/22 10:46:10 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void	print_ast(t_ast *node)
{
	t_word	*word;

	if (!node)
		return ;
	print_ast(node->left);
	if (node->token == SEMICOL)
		ft_putstr(" ; ");
	else if (node->token == OR)
		ft_putstr(" || ");
	else if (node->token == AND)
		ft_putstr(" && ");
	else if (node->token == PIPE)
		ft_putstr(" | ");
	else
	{
		word = node->arglist;
		while (word)
		{
			if (word != node->arglist)
				ft_putchar(' ');
			ft_putstr(word->str);
			word = word->next;
		}
	}
	print_ast(node->right);
}

void		start_jobs(t_env **env, t_job *first_job)
{
	t_job	*j;
	int		j_c;

	(void)env;
	j = first_job;
	j_c = 0;
	while (j)
	{
		printf("Job %d (%s) :\n", ++j_c, j->is_background ? "BG" : "FG");
		print_ast(j->arg_tree);
		ft_putchar('\n');
		j = j->next;
	}
}

/*void	start_job(t_env **env, t_job *j, int foreground)
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
		// Set up pipes, if necessary.
		if (p->next)
		{
			if (pipe(mypipe) < 0)
				exit_error("pipe() error");
			outfile = mypipe[1];
		}
		else
			outfile = j->stdout;
		// Fork the child processes.
		if ((pid = fork ()) == -1)
			exit_error("fork() error");
		else if (pid == 0)
		{
			// This is the child process.
			//launch_process(p, j->pgid, infile, outfile, j->stderr, foreground);
			start_command(env, env, p->args, NULL);
		}
		else
		{
			// This is the parent process.
			p->pid = pid;
			if (g_shell.is_interactive)
			{
				if (!j->pgid)
					j->pgid = pid;
				setpgid(pid, j->pgid);
			}
		}
		// Clean up after pipes.
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
}*/
