/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 12:03:19 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/24 13:26:15 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void	replace_exec_name(char **arg, char *newname)
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

int			start_command(t_env **env, t_env **cmd_env, char **args, t_redirect **redir_array)
{
	int		ret;
	int		ret_builtin;
	char	*after_path;
	int		notfound;
	int		fdsave_array[1024];

	ret = 0;
	if (!args[0])
		return (0);
	notfound = 1;
	save_filedes(fdsave_array, 1024);
	apply_redirects(redir_array);
	if ((ret_builtin = search_start_builtin(cmd_env, args)) == -2)
	{
		if (ft_strchr(args[0], '/'))
		{
			if (is_there_a_file(args[0]))
				notfound = 0;
		}
		else if ((after_path = find_cmd_path(env, cmd_env, args[0])))
		{
			replace_exec_name(&args[0], after_path);
			notfound = 0;
		}
		if (notfound == 1)
		{
			ft_fminiprint(2, "%l0s%: Command not found.\n", args[0]);
			return (1);
		}
		ret = try_start_process(cmd_env, args);
	}
	else if (ret_builtin == -1)
		ret = 1;
	restore_filedes(fdsave_array, 1024);
	return (ret);
}
