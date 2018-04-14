/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 12:10:52 by acauchy           #+#    #+#             */
/*   Updated: 2018/02/21 16:21:26 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MINISHELL_H
# define __MINISHELL_H

# include <stdio.h>

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# define BUILTIN_MAX 42
# define INPUT_MAX_LEN 16384
# define PARAMS_MAX 512
# define MAX_PATH_SIZE 4096

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_builtin
{
	char	*name;
	int		(*func)(t_env**, char**);
}					t_builtin;

extern int			g_running_proc;
extern t_env		**g_envptr;

/*
** utils.c
*/

void				exit_error(char *errmsg);
int					is_there_a_file(char *filepath);
int					is_executable(char *filepath);

/*
** builtin_manager.c
*/

void				clear_builtins(void);
void				load_builtin(char *name, int (*func)(t_env**, char**));
int					search_start_builtin(t_env **env, char **args);

/*
** builtin_[builtin_name].c
*/

int					builtin_exit(t_env **env, char **args);
int					builtin_pwd(t_env **env, char **args);
int					builtin_cd(t_env **env, char **args);
int					builtin_env(t_env **env, char **args);
int					builtin_setenv(t_env **env, char **args);
int					builtin_unsetenv(t_env **env, char **args);
int					builtin_echo(t_env **env, char **args);

/*
** s_env.c
*/

void				clear_env(t_env *env);
void				unset_env(t_env **head, char *key);
void				set_env(t_env **head, char *key, char *value);
t_env				*copy_env(t_env **env);

/*
** env.c
*/

void				print_env(t_env **env);
char				*read_from_env(t_env **env, char *key);
char				**env_to_array(t_env **env);

/*
** parser.c
*/

char				**parse_input(char *input, char **errmsg);
void				delete_args(char **args);

/*
** signals.c
*/

void				init_signals(void);

/*
** input.c
*/

char				*ask_for_input(int fd, t_env **env, char **errmsg);

/*
** output.c
*/

void				print_prompt(t_env **env);
void				print_sig_error(int sig);
void				print_chdir_error(char *path);

/*
** process.c
*/

int					start_process(t_env **env, char **args);

/*
** path.c
*/

char				*find_cmd_path(t_env **env, t_env **cmd_env, char *cmd);

/*
** init.c
*/

void				init_env(t_env **env, char **envp);
void				init_builtins(void);

/*
** starter.c
*/

void				start_command(t_env **env, t_env **cmd_env, char **args);

#endif
