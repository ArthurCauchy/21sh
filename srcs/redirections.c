/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 10:59:12 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/18 11:17:11 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int	open_file_fd(char *filename, int append)
{
	int	flags;

	if (append)
		flags = O_CREAT | O_APPEND;
	else
		flags = O_CREAT;
	if (open(filename, flags, 0644) == -1)
		return (-1);
	return (0);
}
