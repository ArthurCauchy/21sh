/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 12:03:19 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/14 12:55:02 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_env		**g_envptr = NULL;

static void	init_minishell(t_env **env, char **envp)
{
	init_signals();
	init_builtins();
	init_env(env, envp);
	g_envptr = env;
}

static void	print_n_free_errmsg(char **errmsg)
{
	ft_putendl_fd(*errmsg, 2);
	free(*errmsg);
	*errmsg = NULL;
}

static int	input_and_parse(t_env **env, char ***args)
{
	char	*errmsg;
	char	*rep;

	errmsg = NULL;
	rep = ask_for_input(0, env, &errmsg);
	if (errmsg)
	{
		print_n_free_errmsg(&errmsg);
		free(rep);
		return (-1);
	}
	*args = parse_input(rep, &errmsg);
	free(rep);
	if (errmsg)
	{
		print_n_free_errmsg(&errmsg);
		return (-1);
	}
	return (0);
}

int			main(int argc, char **argv, char **envp)
{
	char	**args;
	t_env	*env;

	(void)argc;
	(void)argv;
	env = NULL;
	init_minishell(&env, envp);
	while (42)
	{
		if (input_and_parse(&env, &args) == 0)
		{
			start_command(&env, &env, args);
			delete_args(args);
		}
	}
	return (EXIT_SUCCESS);
}
