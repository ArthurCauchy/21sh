/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 11:34:35 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/14 11:32:31 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	print_n_free_errmsg(char **errmsg)
{
	ft_putendl_fd(*errmsg, 2);
	free(*errmsg);
	*errmsg = NULL;
}

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
