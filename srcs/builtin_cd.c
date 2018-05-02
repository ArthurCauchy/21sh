/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:06:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/02 17:31:46 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

/*static int	try_cd(char *options, t_env **env, char *path)
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
		return (1);
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
}*/

static int	try_cd_p(t_env **env, char *path)
{
	char	curpath[MAX_PATH_SIZE];
	char	curr_pwd[MAX_PATH_SIZE];
	char	old_pwd[MAX_PATH_SIZE];
	char	*success;
	
	if (!(path[0] == '/' || ft_strcmp(path, ".") == 0 || ft_strcmp(path, "..") == 0))
		(void)0; // TODO handle CDPATH - be careful with the size of curpath
	ft_strncpy(curpath, path, MAX_PATH_SIZE);
	success = getcwd(old_pwd, MAX_PATH_SIZE);
	if (chdir(curpath) == -1)
	{
		print_chdir_error(path);
		return (1);
	}
	if (success)
		set_env(env, ft_strdup("OLDPWD"), ft_strdup(old_pwd));
	if (!getcwd(curr_pwd, MAX_PATH_SIZE))
	{
		ft_putendl_fd("cd: Error with the new current directory.", 2);
		return (1);
	}
	set_env(env, ft_strdup("PWD"), ft_strdup(curr_pwd)); // must code pwd -P builtin before ! (ref: posix)
	return (0);
}

/*static int	try_cd_l(t_env **env, char *path)
{
	char	*curpath;
	char	buff[MAX_PATH_SIZE];
	char	*old_env_pwd;
	
	if (!(path[0] == '/' || ft_strcmp(path, ".") == 0 || ft_strcmp(path, "..") == 0))
		(void)0; // TODO handle CDPATH - be careful with the size of curpath
	ft_strncpy(buff, path, MAX_PATH_SIZE);
	old_env_pwd = read_from_env(env, "PWD");
	
	curpath = ft_strjoin(old_env_pwd );
	return (0);
}*/

static int	try_cd(char *options, t_env **env, char *path)
{
	if (ft_strchr(options, 'p') && (!ft_strchr(options, 'l') || ft_strchr(options, 'p') > ft_strchr(options, 'l')))
		return (try_cd_p(env, path));
	else
		return (try_cd_p(env, path));
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

	ft_bzero(options, 4096);
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
