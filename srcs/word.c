/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 10:29:04 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/11 11:39:15 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_word	*new_word(char *str)
{
	t_word	*new;
	char	*dup_str;

	if (!(new = (t_word*)malloc(sizeof(t_word))))
		exit_error("malloc() error");
	if (!(dup_str = ft_strdup(str)))
		exit_error("ft_strdup() error");
	new->str = dup_str;
	new->next = NULL;
	return (new);
}

void	delete_wordlist(t_word **head)
{
	t_word	*cur;
	t_word	*prev;

	cur = *head;
	prev = NULL;
	while (cur)
	{
		if (cur->str)
			free(cur->str);
		prev = cur;
		cur = cur->next;
		free(prev);
	}
	*head = NULL;
}
