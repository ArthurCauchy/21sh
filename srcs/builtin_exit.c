/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:06:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/17 11:46:38 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int	builtin_exit(t_env **env, char **args)
{
	int	exit_status;

	(void)env;
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
	g_exitnow = 1;
	g_exitstatus = exit_status;
	return(0);
}
