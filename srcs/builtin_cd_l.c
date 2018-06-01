/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_l.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:06:00 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/01 16:07:35 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"

static char 	*add_final_slash(char **path)
{
	if ((*path)[ft_strlen(*path) - 1] != '/')
		*path = ft_strjoin_free(*path, ft_strdup("/"));
	return (*path);
}

static void		add_to_compo_lst(t_list **list, char *buff)
{
	char	*str;
	char	**ptr;
	t_list	*new;

	if (ft_strlen(buff) < 1)
		return ;
	if (!(ptr = malloc(sizeof(char*))))
		exit_error("malloc() error");
	str = ft_strdup(buff);
	*ptr = str;
	new = ft_lstnew(ptr, sizeof(char*));
	free(ptr);
	ft_lstpushback(list, new);
}

static void		remove_from_compo_lst(t_list **list, t_list *to_rm)
{
	t_list	*prev;
	t_list	*cur;

	prev = NULL;
	cur = *list;
	while (cur)
	{
		if (cur == to_rm)
		{
			if (cur == *list)
				*list = cur->next;
			prev->next = cur->next;
			free(*((char**)cur->content));
			free(cur->content);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

static t_list	*str_to_compo(char *str)
{
	t_list	*list;
	char	inslash;
	size_t	i;
	size_t	j;
	char	buff[MAX_PATH_SIZE];

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
		if (!inslash || j == 0)
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
	char	buff[MAX_PATH_SIZE * 2];
	char	c;
	size_t	i;
	size_t	j;
	
	prev = NULL;
	i = 0;
	while (list)
	{
		j = 0;
		while ((c = (*((char**)list->content))[j++]))
			buff[i++] = c;
		free(*((char**)list->content));
		free(list->content);
		prev = list;
		list = list->next;
		free(prev);
	}
	buff[i] = '\0';
	return (ft_strdup(buff));
}


static void		simplify_path_dot(t_list **list)
{
	t_list	*prev;
	t_list	*cur;
	t_list	*next;

	prev = NULL;
	cur = *list;
	while (cur)
	{
		next = cur->next;
		if (ft_strcmp(*((char**)cur->content), ".") == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				*list = cur->next;
			free(*((char**)cur->content));
			free(cur->content);
			free(cur);
		}
		else
			prev = cur;
		cur = next;
	}
}

static void		simplify_path_dotdot(t_list **list)
{
	t_list	*prev_dir;
	t_list	*cur;

	prev_dir = NULL;
	cur = *list;
	while (cur)
	{
		if (ft_strcmp(*((char**)cur->content), "..") != 0 && ft_strcmp(*((char**)cur->content), "/") != 0)
			prev_dir = cur;
		if (ft_strcmp(*((char**)cur->content), "..") == 0)
		{
			if (prev_dir)
				remove_from_compo_lst(list, prev_dir);
			remove_from_compo_lst(list, cur);
			prev_dir = NULL;
			cur = *list;
			continue;
		}
		cur = cur->next;
	}
}

static void		simplify_path_slash(t_list **list)
{
	t_list	*prev;
	t_list	*cur;

	prev = NULL;
	cur = *list;
	while (cur)
	{
		if (prev && ((ft_strchr(*((char**)prev->content), '/')) || !cur->next)
				&& (ft_strchr(*((char**)cur->content), '/')))
		{
			prev->next = cur->next;
			free(*((char**)cur->content));
			free(cur->content);
			free(cur);
			prev = NULL;
			cur = *list;
			continue;
		}
		prev = cur;
		cur = cur->next;
	}
}

int				try_cd_l(t_env **env, char *path)
{
	char	*curpath;
	char	buff[MAX_PATH_SIZE];
	char	*old_env_pwd;
	t_list	*comp_lst;
	
	ft_strncpy(buff, path, MAX_PATH_SIZE);
	if (!(old_env_pwd = read_from_env(env, "PWD")))
	{
		ft_putendl_fd("cd: PWD env variable not found !", 2);
		return (1);
	}
	if (buff[0] != '/')
		curpath = ft_strjoin(add_final_slash(&old_env_pwd), buff);
	else
		curpath = ft_strdup(buff);
	free(old_env_pwd);
	comp_lst = str_to_compo(curpath);
	simplify_path_dot(&comp_lst);
	simplify_path_dotdot(&comp_lst);
	simplify_path_slash(&comp_lst);
	free(curpath);
	curpath = compo_to_str(comp_lst);
	if (chdir(curpath) == -1)
	{
		print_chdir_error(path);
		free(curpath);
		return (1);
	}
	set_env(env, ft_strdup("OLDPWD"), read_from_env(env, "PWD"));
	set_env(env, ft_strdup("PWD"), ft_strdup(curpath));
	free(curpath);
	return (0);
}
