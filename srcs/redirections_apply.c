#include "21sh.h"


/*
** mode :
** 0) read
** 1) write
*/

static int	open_file_fd(char *filename, int mode, int append)
{
	int flags;
	int fd;
	
	if (append)
		flags = O_CREAT | O_APPEND;
	else
		flags = O_CREAT;
	if (mode == 0)
		flags = flags | O_RDONLY;
	else if (mode == 1)
		flags = flags | O_WRONLY;
	fd = open(filename, flags, 0644);
	return (fd);
}

static void	apply_redirect_pipe(t_redirect *redir)
{
	dup2(ft_atoi(redir->right), ft_atoi(redir->left));
}

static void	apply_redirect_lshift(t_redirect *redir)
{
	int	left_fd;
	int	file_fd;
	
	left_fd = ft_atoi(redir->left);
	file_fd = open_file_fd(redir->right, 0, 0);
	dup2(file_fd, left_fd);
}

static void	apply_redirect_rshift(t_redirect *redir)
{
	int	left_fd;
	int	file_fd;
	
	if (ft_strlen(redir->left) > 0)
		left_fd = ft_atoi(redir->left);
	else
		left_fd = 1;
	file_fd = open_file_fd(redir->right, 1, 0);
	dup2(file_fd, left_fd);
}

static void	apply_redirect_rshift2(t_redirect *redir)
{
	int	left_fd;
	int	file_fd;
	
	if (ft_strlen(redir->left) > 0)
		left_fd = ft_atoi(redir->left);
	else
		left_fd = 1;
	file_fd = open_file_fd(redir->right, 1, 1);
	dup2(file_fd, left_fd);
}

void		apply_redirects(t_redirect **redir_array)
{
	size_t  i;

	i = 0;
	while (i < REDIRECT_MAX && redir_array[i] != NULL)
	{
		if (redir_array[i]->token == PIPE)
			apply_redirect_pipe(redir_array[i]);
		else if (redir_array[i]->token == LSHIFT)
			apply_redirect_lshift(redir_array[i]);
		else if (redir_array[i]->token == RSHIFT)
			apply_redirect_rshift(redir_array[i]);
		else if (redir_array[i]->token == RSHIFT2)
			apply_redirect_rshift2(redir_array[i]);
		++i;
	}
}
