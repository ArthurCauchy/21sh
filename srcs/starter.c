/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 12:03:19 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/27 15:07:24 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static int	try_start_process(t_env **cmd_env, t_process *proc)
{
	if (is_executable(proc->path))
		return (start_process(cmd_env, proc));
	ft_fminiprint(2, "%l0s%: Permission denied.\n", proc->args[0]);
	return (1);
}

static void	reset_fdsave_array(int *fdsave_array)
{
	size_t	i;

	i = 0;
	while (i < FD_MAX)
	{
		fdsave_array[i] = -1;
		++i;
	}
}

static int	command_file_exist(char *name)
{
	if (ft_strchr(name, '/') && is_there_a_file(name))
		return (1);
	return (0);
}

int			start_command(t_env **env, t_env **cmd_env, t_process *proc)
{
	int				ret;
	char			*errmsg;
	t_builtin_fct	builtin;
	char			*after_path;
	int				fdsave_array[FD_MAX];

	ret = 0;
	errmsg = NULL;
	if (!proc->args[0])
		return (0);
	reset_fdsave_array(fdsave_array);
	if (apply_redirects(proc->redirs, fdsave_array, &errmsg) == -1)
	{
		print_n_free_errmsg(&errmsg);
		restore_filedes(fdsave_array);
		return (1);
	}
	if ((builtin = search_builtin(proc->args[0])))
		ret = builtin(cmd_env, proc->args);
	else if (command_file_exist(proc->args[0]))
		ret = try_start_process(cmd_env, proc);
	else if (!ft_strchr(proc->args[0], '/') &&
			(after_path = find_cmd_path(env, cmd_env, proc->args[0])))
	{
		proc->path = after_path;
		ret = try_start_process(cmd_env, proc);
	}
	else
	{
		ft_fminiprint(2, "%l0s%: Command not found.\n", proc->args[0]);
		ret = 1;
	}
	restore_filedes(fdsave_array);
	return (ret);
}
