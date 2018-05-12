/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:06:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/12 17:32:35 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int	try_cd_p(t_env **env, char *path)
{
	char	curpath[MAX_PATH_SIZE];
	char	curr_pwd[MAX_PATH_SIZE];
	char	old_pwd[MAX_PATH_SIZE];
	char	*success;
	
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
