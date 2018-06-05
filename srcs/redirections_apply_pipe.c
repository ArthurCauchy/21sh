/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_apply_pipe.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:30:38 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/05 09:57:49 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

int	apply_redirect_pipe(t_redirect *redir, int *fdtmp_array, int *fdsave_array, char **errmsg)
{
	(void)errmsg;
	if (fdtmp_array && fdsave_array)
		save_filedes(fdtmp_array, fdsave_array, ft_atoi(redir->left));
	dup2(ft_atoi(redir->right), ft_atoi(redir->left));
	return (0);
}
