/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 12:03:19 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/18 15:14:26 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int			g_exitnow = 0;
int			g_exitstatus = 0;
t_env		**g_envptr = NULL;

static void	init_shell(t_env **env, char **envp)
{
	init_signals();
	init_builtins();
	init_env(env, envp);
	g_envptr = env;
}

static int	input_and_parse(t_ast **ast)
{
	char	*errmsg;
	char	*rep;
	t_word	*wordlist;

	errmsg = NULL;
	wordlist = NULL;
	rep = ask_for_input(0, g_envptr, &errmsg);
	if (errmsg)
	{
		print_n_free_errmsg(&errmsg);
		free(rep);
		return (-1);
	}
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
	init_shell(&env, envp);
	while (g_exitnow != 1)
	{
		if (input_and_parse(&ast) == 0)
		{
			exec_ast(ast, 0, 1);
			delete_ast(&ast);
		}
	}
	clear_env(env);
	clear_builtins();
	return (g_exitstatus);
}
