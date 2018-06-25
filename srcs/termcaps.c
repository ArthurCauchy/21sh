/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 16:49:21 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/25 17:03:02 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

t_termcaps	*load_termcaps(void)
{
	t_termcaps *new;

	if (!(new = (t_termcaps*)ft_memalloc(sizeof(t_termcaps))))
		exit_error("malloc() error");
	new->go_col = tgetstr("ch", NULL);
	new->go_right = tgetstr("nd", NULL);
	new->go_left = tgetstr("le", NULL);
	new->go_up = tgetstr("up", NULL);
	new->go_down = tgetstr("do", NULL);
	new->del_one_char = tgetstr("dc", NULL);
	new->del_line = tgetstr("ce", NULL);
	if (!new->go_col || !new->go_left || !new->del_one_char
			|| !new->go_up || !new->go_down || !new->del_one_char
			|| !new->del_line)
	{
		free(new);
		return (NULL);
	}
	return (new);
}
