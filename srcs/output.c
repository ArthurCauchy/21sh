/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 09:35:34 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/26 11:51:29 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

/*
** returns the printed prompt size (columns used)
*/

int		print_prompt(t_env **env)
{
	char		*user;
	static char	hostname[1024];
	size_t		ret;

	ret = 0;
	ft_putstr("\033[1;33;40m");
	if ((user = read_from_env(env, "USER")))
	{
		ft_putstr(user);
		ft_putchar('@');
		ret += ft_strlen(user) + 1;
	}
	if (gethostname(hostname, 1024) == -1)
		exit_error("Can't get hostname.");
	ft_putstr(hostname);
	ft_putstr(" % ");
	ft_putstr("\033[0m");
	ret += ft_strlen(hostname) + 3;
	free(user);
	return (ret);
}

int		print_heredoc_prompt(t_env **env)
{
	(void)env;
	ft_putstr("? ");
	return (2);
}

void	print_sig_error(int sig)
{
	if (sig == SIGABRT)
		ft_putendl_fd("Abort", 2);
	else if (sig == SIGBUS)
		ft_putendl_fd("Bus error", 2);
	else if (sig == SIGFPE)
		ft_putendl_fd("Floating Point Exception", 2);
	else if (sig == SIGILL)
		ft_putendl_fd("Illegal instruction", 2);
	else if (sig == SIGSEGV)
		ft_putendl_fd("Segmentation Fault", 2);
	else if (sig == SIGTERM)
		ft_putendl_fd("Terminated", 2);
	else if (sig != SIGINT && sig != SIGPIPE)
		ft_putendl_fd("Unknown fatal signal recieved.", 2);
}

void	print_chdir_error(char *path)
{
	if (is_there_a_file(path))
		ft_fminiprint(2, "%l0s%: Permission denied.\n", path);
	else
		ft_fminiprint(2, "%l0s%: No such file or directory.\n", path);
}
