#include "21sh.h"

void	apply_redirect_lshift(t_redirect *redir)
{
	int	left_fd;
	int	file_fd;

	left_fd = ft_atoi(redir->left);
	file_fd = open_file_fd(redir->right, 0, 0);
	dup2(file_fd, left_fd);
}
