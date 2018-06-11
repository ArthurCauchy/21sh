/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termdata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 18:21:39 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/11 18:26:41 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

void	init_termdata(t_termdata *termdata)
{
	termdata->cur_col = 0;
	termdata->cur_row = 0;
	termdata->max_row = 0;
}
