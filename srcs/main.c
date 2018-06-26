/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 12:03:19 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/26 12:47:49 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

t_shell		g_shell;

static int	do_parsing(t_ast **ast, t_word **wordlist)
{
	char	*errmsg;

	errmsg = NULL;
	syntax_analysis(wordlist, ast);
	if (validate_ast(*ast, &errmsg) != 0)
	{
		print_n_free_errmsg(&errmsg);
		delete_ast(ast);
		clear_heredocs_fds();
		return (-1);
	}
	return (0);
}

static int	do_lexing(t_ast **ast, char *cmd)
{
	int		ret;
	char	*errmsg;
	t_word	*wordlist;

	errmsg = NULL;
	wordlist = NULL;
	lex_analysis(cmd, &wordlist, &errmsg);
	if (errmsg)
	{
		print_n_free_errmsg(&errmsg);
		ret = -1;
	}
	else
	{
		if (apply_heredocs(wordlist, &errmsg) == -1)
		{
			if (errmsg)
				print_n_free_errmsg(&errmsg);
			ret = -1;
			clear_heredocs_fds();
		}
		else
			ret = do_parsing(ast, &wordlist);
	}
	delete_wordlist(&wordlist);
	return (ret);
}

static int	input_and_parse(t_ast **ast)
{
	int		ret;
	char	*cmd;

	cmd = ask_for_input();
	if (ft_strlen(cmd) > 0)
		add_history_elem(&g_shell.history, cmd);
	ret = do_lexing(ast, cmd);
	free(cmd);
	return (ret);
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
		g_shell.nb_cols = get_term_cols();
		if (input_and_parse(&ast) == 0)
		{
			g_shell.abort_command = 0;
			g_shell.last_command_status = exec_ast(ast, NULL, NULL);
			clear_heredocs_fds();
		}
		else
			g_shell.last_command_status = 1;
		delete_ast(&ast);
	}
	clear_all();
	return (g_shell.exit_status);
}
