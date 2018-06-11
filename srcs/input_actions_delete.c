/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions_delete.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:05:50 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/11 17:41:15 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	input_action_delete(char *line, size_t *cur, size_t *cur_term)
{
	size_t	i;

	(void)cur_term;
	if (*cur > 0)
	{
		--*cur;
		i = *cur;
		while (line[i])
		{
			line[i] = line[i + 1];
			++i;
		}
	}
}
