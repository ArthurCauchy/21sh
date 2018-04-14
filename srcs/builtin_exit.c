/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:06:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/02/05 12:11:21 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(t_env **env, char **args)
{
	int	exit_status;

	exit_status = 0;
	if (args[1])
	{
		exit_status = ft_atoi(args[1]);
		if (args[2])
		{
			ft_putendl_fd("exit: Too many arguments.", 2);
			return (-1);
		}
	}
	delete_args(args);
	clear_env(*env);
	clear_builtins();
	exit(exit_status);
}
