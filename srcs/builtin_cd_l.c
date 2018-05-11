/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_l.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:06:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/05/02 17:31:46 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static char 	*add_final_slash(char **path)
{
	if ((*path)[ft_strlen(*path) - 1] != '/')
		*path = ft_strjoin_free(*path, ft_strdup("/"));
	return (*path);
}

/*static void	simplify_path(t_fakestr *path)
{
	// remove /./ sequences
	// simplify ../ sequences (posix cd step 8.b)
	// remove multiple /
}*/

static void add_to_compo_lst(t_list **list, char *buff)
{
	char		*str;
	t_list	*new;

	if (ft_strlen(buff) < 1)
		return ;
	str = ft_strdup(buff);
	new = ft_lstnew(&str, sizeof(char*));
	ft_lstpushback(list, new);
}

static t_list	*str_to_compo(char *str)
{
	t_list	*list;
	char		inslash;
	size_t	i;
	size_t	j;
	char		buff[MAX_PATH_SIZE];

	list = NULL;
	inslash = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if ((!inslash && str[i] == '/') || (inslash && str[i] != '/'))
		{
			buff[j] = '\0';
			add_to_compo_lst(&list, buff);
			inslash = inslash ? 0 : 1;
			j = 0;
		}
		buff[j++] = str[i];
		++i;
	}
	buff[j] = '\0';
	add_to_compo_lst(&list, buff);
	return (list);
}

static char	*compo_to_str(t_list *list)
{
	t_list	*prev;
	char		buff[MAX_PATH_SIZE * 2];
	char		c;
	size_t	i;
	size_t	j;
	
	prev = NULL;
	i = 0;
	while (list)
	{
		j = 0;
		while ((c = ((char*)list->content)[j++]))
			buff[i++] = c;
		//free(*((char*)list->content));
		free(list->content);
		prev = list;
		list = list->next;
		free(prev);
	}
	buff[i] = '\0';
	return (ft_strdup(buff));
}

int						try_cd_l(t_env **env, char *path)
{
	char		*curpath;
	char		buff[MAX_PATH_SIZE];
	char		*old_env_pwd;
	t_list	*comp_lst;
	
	if (!(path[0] == '/' || ft_strcmp(path, ".") == 0 || ft_strcmp(path, "..") == 0))
		(void)0; // TODO handle CDPATH - be careful with the size of curpath
	ft_strncpy(buff, path, MAX_PATH_SIZE);
	old_env_pwd = read_from_env(env, "PWD");
	if (buff[0] != '/')
		curpath = ft_strjoin(add_final_slash(&old_env_pwd), buff);
	else
		curpath = ft_strdup(buff);
	free(old_env_pwd);
	comp_lst = str_to_compo(curpath);
	// simplify components list
	free(curpath);
	curpath = compo_to_str(comp_lst);
	ft_putendl(curpath);
	// check curpath length
	if (chdir(curpath) == -1)
	{
		print_chdir_error(path);
		return (1);
	}
	set_env(env, ft_strdup("PWD"), ft_strdup(curpath));
	return (0);
}
