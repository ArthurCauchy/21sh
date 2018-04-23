#include "21sh.h"

void	apply_redirect_pipe(t_redirect *redir)
{
	dup2(ft_atoi(redir->right), ft_atoi(redir->left));
}
