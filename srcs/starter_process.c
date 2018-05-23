/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starter_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 12:03:19 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/23 13:11:24 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

/*static void	replace_exec_name(char **arg, char *newname)
{
	free(*arg);
	*arg = newname;
}

static int	try_start_process(t_env **cmd_env, char **args)
{
	if (is_executable(args[0]))
		return (start_process(cmd_env, args));
	ft_fminiprint(2, "%l0s%: Permission denied.\n", args[0]);
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

int			start_command(t_env **env, t_env **cmd_env,
		char **args, t_redirect **redir_array)
{
	int				ret;
	char			*errmsg;
	t_builtin_fct	builtin;
	char			*after_path;
	int				fdsave_array[FD_MAX];

	ret = 0;
	errmsg = NULL;
	if (!args[0])
		return (0);
	reset_fdsave_array(fdsave_array);
	if (apply_redirects(redir_array, fdsave_array, &errmsg) == -1)
	{
		print_n_free_errmsg(&errmsg);
		restore_filedes(fdsave_array);
		return (1);
	}
	if ((builtin = search_builtin(args[0])))
		ret = builtin(cmd_env, args);
	else if (command_file_exist(args[0]))
		ret = try_start_process(cmd_env, args);
	else if (!ft_strchr(args[0], '/') &&
			(after_path = find_cmd_path(env, cmd_env, args[0])))
	{
		replace_exec_name(&args[0], after_path);
		ret = try_start_process(cmd_env, args);
	}
	else
	{
		ft_fminiprint(2, "%l0s%: Command not found.\n", args[0]);
		ret = 1;
	}
	restore_filedes(fdsave_array);
	return (ret);
}*/
