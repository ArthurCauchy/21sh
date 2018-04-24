#include "21sh.h"

t_redirect	*new_redirect(char *left, char *right, t_token token)
{
	t_redirect	*redirect;

	if (!(redirect = (t_redirect*)malloc(sizeof(t_redirect))))
		exit_error("malloc() error");
	redirect->left = ft_strdup(left);
	redirect->right = ft_strdup(right);
	redirect->token = token;
	return (redirect);
}

void		delete_redir_array(t_redirect **redir_array)
{
	size_t	i;

	i = 0;
	while (i < REDIRECT_MAX && redir_array[i] != NULL)
	{
		free(redir_array[i]->left);
		free(redir_array[i]->right);
		free(redir_array[i]);
		redir_array[i] = NULL;
		++i;
	}
}
