#include "21sh.h"

static int	is_numerical(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		++str;
	}
	return (1);
}

void		apply_redirect_rshift_amp(t_redirect *redir)
{
	int	left_fd;
	int	right_fd;

	if (ft_strlen(redir->left) > 0)
		left_fd = ft_atoi(redir->left);
	else
		left_fd = 1;
	if (!is_numerical(redir->right))
		return ;
	right_fd = ft_atoi(redir->right);
	dup2(right_fd, left_fd);
}
