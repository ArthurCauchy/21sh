/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:06:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/26 16:50:30 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	try_cd(char *options, t_env **env, char *path)
{
	if (ft_strchr(options, 'p') && (!ft_strchr(options, 'l')
				|| ft_strchr(options, 'p') > ft_strchr(options, 'l')))
		return (try_cd_p(env, path));
	else
		return (try_cd_l(env, path));
}

static int	builtin_cd_withargs(char *options, t_env **env, char **args)
{
	char	*oldpwd;
	int		retcode;

	if (args[1])
	{
		ft_putendl_fd("cd: Too many arguments.", 2);
		return (1);
	}
	if (ft_strcmp(args[0], "-") == 0)
	{
		if (!(oldpwd = read_from_env(env, "OLDPWD")))
		{
			ft_putendl_fd("cd: Environment variable 'OLDPWD' not found !", 2);
			return (1);
		}
		retcode = try_cd(options, env, oldpwd);
		free(oldpwd);
		return (retcode);
	}
	return (try_cd(options, env, args[0]));
}

int			builtin_cd(t_env **env, char **args)
{
	char	*home;
	int		retcode;
	int		start;
	char	options[4096];

	start = builtin_parse_options(args, options, 4096);
	if (builtin_validate_options(options, "pl") == -1)
	{
		ft_putendl_fd("Usage : cd [-pl] [-|<dir>].", 2);
		return (1);
	}
	if (args[start])
		return (builtin_cd_withargs(options, env, args + start));
	if (!(home = read_from_env(env, "HOME")))
	{
		ft_putendl_fd("cd: No directory is given and HOME empty"
				" or undefined !", 2);
		return (1);
	}
	retcode = try_cd(options, env, home);
	free(home);
	return (retcode);
}
