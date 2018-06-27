/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 12:03:19 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/27 10:38:26 by arthur           ###   ########.fr       */
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

static void	clear_arrays(int *fdtmp_array, int *fdsave_array)
{
	size_t	i;

	i = 0;
	while (i < FD_MAX)
	{
		fdtmp_array[i] = 0;
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

static int	start_command_builtin(t_env **env,
		t_process *proc, int *fdtmp_array, int *fdsave_array)
{
	int				ret;
	t_builtin_fct	builtin;
	char			*errmsg;

	errmsg = NULL;
	if ((builtin = search_builtin(proc->args[0])) && g_shell.pipe_lvl == 0)
	{
		if (apply_redirects(proc->redirs,
					fdtmp_array, fdsave_array, &errmsg) == -1)
		{
			print_n_free_errmsg(&errmsg);
			restore_filedes(fdtmp_array, fdsave_array);
			return (1);
		}
		ret = builtin(env, proc->args);
	}
	else if (builtin)
		ret = fork_start_builtin(env, proc, builtin);
	else
		ret = -1;
	return (ret);
}

static int	start_command_external(t_env **env, t_env **cmd_env, t_process *proc)
{
	char			*after_path;

	if (command_file_exist(proc->args[0]))
	{
		proc->path = ft_strdup(proc->args[0]);
		return (try_start_process(cmd_env, proc));
	}
	else if (!ft_strchr(proc->args[0], '/') &&
			(after_path = find_cmd_path(env, cmd_env, proc->args[0])))
	{
		proc->path = after_path;
		return (try_start_process(cmd_env, proc));
	}
	else
		return (-1);
}

int			start_command(t_env **env, t_env **cmd_env, t_process *proc)
{
	int				ret;
	int				fdtmp_array[FD_MAX];
	int				fdsave_array[FD_MAX];

	ret = 0;
	if (!proc->args[0])
		return (0);
	clear_arrays(fdtmp_array, fdsave_array);
	if ((ret = start_command_builtin(cmd_env, proc, fdtmp_array, fdsave_array)) == -1)
		ret = start_command_external(env, cmd_env, proc);
	if (ret == -1)
	{
		ft_fminiprint(2, "%l0s%: Command not found.\n", proc->args[0]);
		ret = 1;
	}
	restore_filedes(fdtmp_array, fdsave_array);
	return (ret);
}
