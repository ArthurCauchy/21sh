/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:06:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/30 12:33:04 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static void	add_to_tmp_env(t_env **env, char *str)
{
	char		*eq_char;

	eq_char = ft_strchr(str, '=');
	set_env(env, ft_strsub(str, 0, eq_char - str), ft_strdup(eq_char + 1));
}

int			builtin_env(t_env **env, char **args)
{
	t_env	*tmp_env;
	int		i;
	char	options[4096];

	ft_bzero(options, 4096);
	i = builtin_parse_options(args, options, 4096);
	if (builtin_validate_options(options, "i") == -1)
	{
		ft_putendl_fd("Usage : env [-i] [NAME=VALUE] [COMMAND]", 2);
		return (1);
	}
	tmp_env = NULL;
	if (!ft_strchr(options, 'i'))
		tmp_env = copy_env(env);
	while (args[i] && ft_strchr(args[i], '='))
	{
		add_to_tmp_env(&tmp_env, args[i]);
		++i;
	}
	if (args[i])
		start_command(env, &tmp_env, args + i, NULL);
	else
		print_env(&tmp_env);
	clear_env(tmp_env);
	return (0);
}
