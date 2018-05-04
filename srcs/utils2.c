/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 11:34:35 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/04 15:17:33 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	save_filedes(int *fdsave_array, int fd)
{
	if (fd < FD_MAX && fdsave_array[fd] < 0)
	{
		fdsave_array[fd] = dup(fd);
		printf("\nsaving fd: %d to %d\n", fd, fdsave_array[fd]);
	}
}

void	restore_filedes(int *fdsave_array)
{
	int	i;

	i = 0;
	while (i < FD_MAX)
	{
		if (fdsave_array[i] > 0)
		{
			printf("\nrestoring fd: %d from %d\n", i, fdsave_array[i]);
			dup2(fdsave_array[i], i);
			close(fdsave_array[i]);
		}
		++i;
	}
}
