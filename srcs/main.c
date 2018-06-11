/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 12:03:19 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/11 14:47:16 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

t_shell		g_shell;

static int	input_and_parse(t_ast **ast)
{
	char	*errmsg;
	char	*rep;
	t_word	*wordlist;

	errmsg = NULL;
	wordlist = NULL;
	rep = ask_for_input(g_shell.env);
	// save to history
	lex_analysis(rep, &wordlist, &errmsg);
	free(rep);
	if (errmsg)
	{
		print_n_free_errmsg(&errmsg);
		delete_wordlist(&wordlist);
		return (-1);
	}
	syntax_analysis(&wordlist, ast);
	delete_wordlist(&wordlist);
	if (validate_ast(*ast, &errmsg) != 0)
	{
		print_n_free_errmsg(&errmsg);
		delete_ast(ast);
		return (-1);
	}
	return (0);
}

int			main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_ast	*ast;

	(void)argc;
	(void)argv;
	env = NULL;
	ast = NULL;
	init(&env, envp);
	while (g_shell.exit_now != 1)
	{
		if (input_and_parse(&ast) == 0)
		{
			g_shell.abort_command = 0;
			g_shell.last_command_status = exec_ast(ast, NULL, NULL);
			delete_ast(&ast);
		}
		else
			g_shell.last_command_status = 1;
	}
	clear_env(env);
	clear_builtins();
	if (g_shell.saved_processes)
		delete_processes(g_shell.saved_processes);
	return (g_shell.exit_status);
}
