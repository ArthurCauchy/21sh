#include "21sh.h"


/*
** mode :
** 0) read
** 1) write
*/

int	open_file_fd(char *filename, int mode, int append)
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
		else if (redir_array[i]->token == LSHIFT_AMP)
			apply_redirect_lshift_amp(redir_array[i]);
		else if (redir_array[i]->token == RSHIFT)
			apply_redirect_rshift(redir_array[i]);
		else if (redir_array[i]->token == RSHIFT_AMP)
			apply_redirect_rshift_amp(redir_array[i]);
		else if (redir_array[i]->token == RSHIFT2)
			apply_redirect_rshift2(redir_array[i]);
		++i;
	}
}
