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
