/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 14:08:29 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/08 14:36:14 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static t_history	*create_history_elem(char *cmd)
{
	t_history	*new;

	if (!(new = (t_history*)malloc(sizeof(t_history))))
		exit_error("malloc() error");
	new->next = NULL;
	new->cmd = ft_strdup(cmd);
	return (new);
}

void		add_history_elem(t_history **history, char *cmd)
{
	t_history	*new;

	new = create_history_elem(cmd);
	new->next = *history;
	*history = new;
}

void		delete_history(t_history *history)
{
	t_history	*prev;
	t_history	*cur;

	prev = NULL;
	cur = history;
	while (cur)
	{
		prev = cur;
		cur = cur->next;
		free(prev->cmd);
		free(prev);
	}
}
