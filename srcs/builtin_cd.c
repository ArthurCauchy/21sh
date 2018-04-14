/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:06:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/02/21 16:27:57 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int	try_cd(t_env **env, char *path)
{
	char	curr_pwd[MAX_PATH_SIZE];
	char	*curr_pwd_env;
	int		nocurr;

	curr_pwd_env = NULL;
	nocurr = 0;
	if (!getcwd(curr_pwd, MAX_PATH_SIZE)
			&& !(curr_pwd_env = read_from_env(env, "PWD")))
		nocurr = 1;
	if (chdir(path) == -1)
	{
		print_chdir_error(path);
		return (-1);
	}
	if (nocurr)
		set_env(env, ft_strdup("OLDPWD"), ft_strdup("/"));
	else if (curr_pwd_env)
		set_env(env, ft_strdup("OLDPWD"), curr_pwd_env);
	else
		set_env(env, ft_strdup("OLDPWD"), ft_strdup(curr_pwd));
	if (!getcwd(curr_pwd, MAX_PATH_SIZE))
		exit_error("getcwd() error");
	set_env(env, ft_strdup("PWD"), ft_strdup(curr_pwd));
	return (0);
}

static int	builtin_cd_withargs(t_env **env, char **args)
{
	char	*oldpwd;
	int		retcode;

	if (args[2])
	{
		ft_putendl_fd("cd: Too many arguments.", 2);
		return (-1);
	}
	if (ft_strcmp(args[1], "-") == 0)
	{
		if (!(oldpwd = read_from_env(env, "OLDPWD")))
		{
			ft_putendl_fd("cd: Environment variable 'OLDPWD' not found !", 2);
			return (-1);
		}
		retcode = try_cd(env, oldpwd);
		free(oldpwd);
		return (retcode);
	}
	return (try_cd(env, args[1]));
}

int			builtin_cd(t_env **env, char **args)
{
	char	*home;
	int		retcode;

	if (args[1])
		return (builtin_cd_withargs(env, args));
	else
	{
		if (!(home = read_from_env(env, "HOME")))
		{
			ft_putendl_fd("No directory is given and HOME empty"
					" or undefined !", 2);
			return (-1);
		}
		retcode = try_cd(env, home);
		free(home);
		return (retcode);
	}
}
