#include "21sh.h"

void	apply_redirect_rshift(t_redirect *redir)
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
