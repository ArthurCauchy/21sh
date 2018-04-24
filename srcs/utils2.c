/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 11:34:35 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/24 13:52:21 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	save_filedes(int *fdsave_array, size_t fdmax)
{
	size_t	i;

	i = 0;
	while (i < fdmax)
	{
		fdsave_array[i] = dup(i);
		++i;
	}
}

void	restore_filedes(int *fdsave_array, size_t fdmax)
{
	size_t	i;

	i = 0;
	while (i < fdmax)
	{
		if (fdsave_array[i] > 0)
		{
			dup2(fdsave_array[i], i);
			close(fdsave_array[i]);
		}
		++i;
	}
}
