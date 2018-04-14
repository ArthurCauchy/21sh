/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:06:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/02/08 14:35:35 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			builtin_echo(t_env **env, char **args)
{
	ssize_t	i;

	(void)env;
	i = 1;
	while (args[i])
	{
		if (i != 1)
			ft_putchar(' ');
		ft_putstr(args[i]);
		++i;
	}
	ft_putchar('\n');
	return (0);
}
