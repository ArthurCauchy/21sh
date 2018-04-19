#include "21sh.h"

t_redirect	*new_redirect(int fd_in, int fd_out, char direction)
{
	t_redirect	*redirect;

	if (!(redirect = (t_redirect*)malloc(sizeof(t_redirect))))
		exit_error("malloc() error");
	redirect->fd_in = fd_in;
	redirect->fd_out = fd_out;
	redirect->direction = direction;
	return (redirect);
}
