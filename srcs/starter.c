/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 12:03:19 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/25 13:51:21 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

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

int			start_command(t_env **env, t_env **cmd_env,
		char **args, t_redirect **redir_array)
{
	int				ret;
	t_builtin_fct	builtin;
	char			*after_path;
	int				notfound;
	int				fdsave_array[FD_MAX];
	size_t			i;

	ret = 0;
	if (!args[0])
		return (0);
	notfound = 1;
	i = 0;
	while (i < FD_MAX)
		fdsave_array[i++] = -1;
	apply_redirects(redir_array, fdsave_array);
	if ((builtin = search_builtin(args[0])))
		ret = builtin(cmd_env, args);
	else
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
			ret = 1;
		}
		else
			ret = try_start_process(cmd_env, args);
	}
	restore_filedes(fdsave_array);
	return (ret);
}
