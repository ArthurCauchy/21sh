/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 11:34:35 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/01 18:31:23 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	save_filedes(int *fdsave_array, int fd)
{
	if (fd < FD_MAX && fdsave_array[fd] < 0)
		fdsave_array[fd] = dup(fd);
}

void	restore_filedes(int *fdsave_array)
{
	int	i;

	i = FD_MAX - 1;
	while (i >= 0)
	{
		if (fdsave_array[i] > 0)
		{
			dup2(fdsave_array[i], i);
			close(fdsave_array[i]);
		}
		--i;
	}
}
