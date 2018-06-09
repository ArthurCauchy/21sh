/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_actions_delete.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:05:50 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/09 17:25:21 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	input_action_delete(char *line, size_t *cur)
{
	if (*cur != 0)
	{
		--*cur;
		ft_putstr(g_shell.termcaps->go_left);
	}
	line[*cur] = '\0';
	ft_putstr(g_shell.termcaps->del_one_char);
}
