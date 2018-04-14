/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:06:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/02/06 16:18:37 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_env **env, char **args)
{
	char	curr_dir[MAX_PATH_SIZE];

	(void)env;
	(void)args;
	if (!getcwd(curr_dir, MAX_PATH_SIZE))
	{
		ft_putendl_fd("pwd: Couldn't find the current directory.", 2);
		return (-1);
	}
	ft_putendl(curr_dir);
	return (0);
}
