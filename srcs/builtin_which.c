/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_which.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:06:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/24 17:48:50 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int	builtin_which(t_env **env, char **args)
{
	char	*cmd_path;

	cmd_path = NULL;
	if (!args[1])
	{
		ft_putendl_fd("which: Too few arguments.", 2);
		return (1);
	}
	if (search_builtin(args[1]))
	{
		ft_putstr(args[1]);
		ft_putendl(": shell built-in command.");
	}
	else if (ft_strchr(args[1], '/') && is_there_a_file(args[1])
			&& is_executable(args[1]))
		ft_putendl(args[1]);
	else if (!ft_strchr(args[1], '/') &&
			(cmd_path = find_cmd_path(env, env, args[1]))
			 && is_executable(cmd_path))
		ft_putendl(cmd_path);
	else
	{
		ft_putstr(args[1]);
		ft_putendl(": Command not found.");
		free(cmd_path);
		return (1);
	}
	free(cmd_path);
	return (0);
}
