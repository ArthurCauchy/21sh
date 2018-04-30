/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 12:07:09 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/30 12:07:10 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int		builtin_parse_options(char **args, char *options, int options_size)
{
	int		i;
	int		j;
	int		k;

	i = 1;
	k = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "--") == 0 || args[i][0] != '-' || !args[i][1])
			break ;
		j = 0;
		while (k < options_size - 1 && args[i][++j])
			if (!ft_strchr(options, args[i][j]))
				options[k++] = args[i][j];
		++i;
	}
	options[k] = '\0';
	return (i);
}

int		builtin_validate_options(char *options, char *valid_set)
{
	size_t	i;

	i = 0;
	while (options[i])
	{
		if (!ft_strchr(valid_set, options[i]))
			return (-1);
		++i;
	}
	return (0);
}
