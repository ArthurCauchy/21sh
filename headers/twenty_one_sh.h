/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twenty_one_sh.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 12:10:52 by acauchy           #+#    #+#             */
/*   Updated: 2018/04/25 13:54:08 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TWENTY_ONE_SH_H
# define __TWENTY_ONE_SH_H

# include <stdio.h>

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# define BUILTIN_MAX 42
# define INPUT_MAX_LEN 16384
# define PARAMS_MAX 512
# define FD_MAX 1024
# define REDIRECT_MAX 512
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

typedef struct		s_lexdata
{
	char	*buff;
	size_t	i;
	size_t	j;
	int		quoted;
}					t_lexdata;

typedef enum		e_token
{
	ARG,
	LSHIFT,
	LSHIFT_AMP,
	LSHIFT2,
	RSHIFT,
	RSHIFT_AMP,
	RSHIFT2,
	AMP,
	PIPE,
	AND,
	OR,
	SEMICOL,
}					t_token;

typedef struct		s_word
{
	t_token			token;
	char			*str;
	struct s_word	*next;
}					t_word;

typedef struct		s_ast
{
	t_token			token;
	t_word			*arglist;
	struct s_ast	*right;
	struct s_ast	*left;
}					t_ast;

typedef struct		s_redirect
{
	char	*left;
	char	*right;
	t_token	token;
}					t_redirect;

typedef int (*t_builtin_fct)(t_env**, char**);

extern int			g_exitnow;
extern int			g_exitstatus;
extern int			g_running_proc;
extern t_env		**g_envptr;

/*
** utils.c, utils2.c
*/

void				exit_error(char *errmsg);
int					is_there_a_file(char *filepath);
int					is_executable(char *filepath);
void				print_n_free_errmsg(char **errmsg);
void				save_filedes(int *fdsave_array, int fd);
void				restore_filedes(int *fdsave_array);

/*
** builtin_manager.c
*/

void				clear_builtins(void);
void				load_builtin(char *name, int (*func)(t_env**, char**));
t_builtin_fct		search_builtin(char *name);

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
** word.c
*/

t_word				*new_word(t_token token, char *str);
void				remove_word(t_word **wordlist, t_word *word);
void				delete_wordlist(t_word **head);

/*
** ast.c
*/

t_ast				*new_ast_node(t_token token, t_word *arglist);
void				delete_ast(t_ast **ast);

/*
** lexing.c, lexing_[token].c
*/

int					lex_is_separator(char c);
void				add_word(t_token token, char *str, t_word **wordlist);
void				lex_analysis(char *cmdline,
		t_word **wordlist, char **errmsg);
void				lex_semicol_word(char *cmdline,
		t_word **wordlist, t_lexdata *lexdata);
void				lex_space_word(char *cmdline,
		t_word **wordlist, t_lexdata *lexdata);
void				lex_amp_and_word(char *cmdline,
		t_word **wordlist, t_lexdata *lexdata);
void				lex_pipe_or_word(char *cmdline,
		t_word **wordlist, t_lexdata *lexdata);
void				lex_shift_src_redirect(char *cmdline,
		t_word **wordlist, t_lexdata *lexdata);
void				lex_shift_dest_redirect(char *cmdline,
		t_word **wordlist, t_lexdata *lexdata);
void				lex_rshift_word(char *cmdline,
		t_word **wordlist, t_lexdata *lexdata);
void				lex_lshift_word(char *cmdline,
		t_word **wordlist, t_lexdata *lexdata);

/*
** parsing.c, parsing_[token].c
*/

void				syntax_analysis(t_word **wordlist, t_ast **root);
void				parse_arg(t_word **symbol, t_ast **current);
void				parse_pipe(t_word **symbol, t_ast **current);
void				parse_and(t_word **symbol, t_ast **current);
void				parse_or(t_word **symbol, t_ast **current);
void				parse_semicol(t_word **symbol, t_ast **current);

/*
** parsing_validator.c
*/

int					validate_ast(t_ast *root, char **errmsg);

/*
** redirect.c
*/

t_redirect			*new_redirect(char *left, char *right, t_token token);
void				delete_redir_array(t_redirect **redir_array);

/*
** redirections.c
*/

void				add_redirect(t_redirect **redir_array,
		char *left, char *right, t_token token);
int					analyze_redirects(t_word **arglist,
		t_redirect **redir_array, char **errmsg);

/*
** redirections_apply.c, redirections_apply_[token].c
*/

int					open_file_fd(char *filename, int mode, int append);
void				apply_redirects(t_redirect **redir_array, int *fdsave_array);
void				apply_redirect_pipe(t_redirect *redir, int *fdsave_array);
void				apply_redirect_lshift(t_redirect *redir, int *fdsave_array);
void				apply_redirect_lshift_amp(t_redirect *redir, int *fdsave_array);
void				apply_redirect_rshift(t_redirect *redir, int *fdsave_array);
void				apply_redirect_rshift_amp(t_redirect *redir, int *fdsave_array);
void				apply_redirect_rshift2(t_redirect *redir, int *fdsave_array);

/*
** interpreter.c, interpreter_[token].c
*/

int					exec_ast(t_ast *node, int inputfd, int outputfd);
int					exec_ast_semicol(t_ast *node, int inputfd, int outputfd);
int					exec_ast_or(t_ast *node, int inputfd, int outputfd);
int					exec_ast_and(t_ast *node, int inputfd, int outputfd);
int					exec_ast_pipe(t_ast *node, int inputfd, int outputfd);
int					exec_ast_arg(t_ast *node, int inputfd, int outputfd);

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

int					start_command(t_env **env,
		t_env **cmd_env, char **args, t_redirect **redir_array);

#endif
