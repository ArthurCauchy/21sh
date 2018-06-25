/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_l.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:06:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/25 16:23:40 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static char		*add_final_slash(char **path)
{
	if ((*path)[ft_strlen(*path) - 1] != '/')
		*path = ft_strjoin_free(*path, ft_strdup("/"));
	return (*path);
}

int				try_cd_l(t_env **env, char *path)
{
	char	*curpath;
	char	buff[MAX_PATH_SIZE];
	char	*old_env_pwd;
	t_list	*comp_lst;

	ft_strncpy(buff, path, MAX_PATH_SIZE);
	if (!(old_env_pwd = read_from_env(env, "PWD")))
	{
		ft_putendl_fd("cd: PWD env variable not found !", 2);
		return (1);
	}
	if (buff[0] != '/')
		curpath = ft_strjoin(add_final_slash(&old_env_pwd), buff);
	else
		curpath = ft_strdup(buff);
	free(old_env_pwd);
	comp_lst = str_to_compo(curpath);
	simplify_path_dot(&comp_lst);
	simplify_path_dotdot(&comp_lst);
	simplify_path_slash(&comp_lst);
	free(curpath);
	curpath = compo_to_str(comp_lst);
	if (chdir(curpath) == -1)
	{
		print_chdir_error(path);
		free(curpath);
		return (1);
	}
	set_env(env, ft_strdup("OLDPWD"), read_from_env(env, "PWD"));
	set_env(env, ft_strdup("PWD"), ft_strdup(curpath));
	free(curpath);
	return (0);
}
