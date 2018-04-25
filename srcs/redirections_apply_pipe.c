/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_apply_pipe.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:30:38 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/25 14:03:07 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	apply_redirect_pipe(t_redirect *redir, int *fdsave_array)
{
	save_filedes(fdsave_array, ft_atoi(redir->left));
	dup2(ft_atoi(redir->right), ft_atoi(redir->left));
}
