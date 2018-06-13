/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twenty_one_sh.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 12:10:52 by acauchy           #+#    #+#             */
/*   Updated: 2018/06/13 15:22:43 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TWENTY_ONE_SH_H
# define __TWENTY_ONE_SH_H

# include <stdio.h>

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include <termios.h>
# include <termcap.h>
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
# define KEYBUFF_SIZE 8

typedef struct	s_env
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
	PIPE,
	PIPECLOSE,
	AND,
	OR,
	SEMICOL,
	AMP
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
	struct s_redirect	*next;
	char				*left;
	char				*right;
	t_token				token;
}					t_redirect;

typedef struct		s_process
{
	struct s_process	*next;
	char				*path;
	char				**args;
	t_redirect			*redirs;
	pid_t				pid;
}					t_process;

typedef struct		s_termdata
{
	int	cur_col;
	int	cur_row;
	int	max_row;
	int	saved_col;
	int	saved_row;
}					t_termdata;

typedef struct		s_history
{
	struct s_history	*next;
	char				*cmd;
}					t_history;

typedef struct		s_termcaps
{
	char	*go_col;
	char	*go_right;
	char	*go_left;
	char	*go_up;
	char	*go_down;
	char	*del_one_char;
	char	*del_line;
}					t_termcaps;

typedef struct		s_shell
{
	int				exit_now;
	int				exit_status;
	t_env			**env;
	int				last_command_status;
	int				abort_command;
	pid_t			shell_pgid;
	int				pipe_lvl;
	pid_t			pipe_pgid;
	t_process		*pipe_processes;
	t_process		*saved_processes;
	int				nb_cols;
	int				cmd_cancel;
	struct termios	orig_termios;
	t_termcaps		*termcaps;
}					t_shell;

typedef int	(*t_builtin_fct)(t_env**, char**);

extern t_shell		g_shell;

/*
** utils.c, utils2.c
*/

void				exit_error(char *errmsg);
int					is_there_a_file(char *filepath);
int					is_executable(char *filepath);
int					is_directory(char *filepath);
void				print_n_free_errmsg(char **errmsg);
int					is_separator(char c);

/*
** utils_redirects.c
*/

void				save_filedes(int *fdtmp_array, int *fdsave_array, int fd);
void				restore_filedes(int *fdtmp_array, int *fdsave_array);

/*
** utils_args.c
*/

void				analyze_arglist(t_word *arglist, char **args);
char				**copy_args(char **args);
void				delete_args(char **args);

/*
** utils_termios.c
*/

void				enable_raw_mode(void);
void				disable_raw_mode(void);
int					get_term_cols(void);

/*
** utils_termcaps.c
*/



/*
** builtin_manager.c
*/

void				clear_builtins(void);
void				load_builtin(char *name, int (*func)(t_env**, char**));
t_builtin_fct		search_builtin(char *name);

/*
** builtins_utils.c
*/

int					builtin_parse_options(char **args,
		char *options, int options_size);
int					builtin_validate_options(char *options, char *valid_set);

/*
** builtin_[builtin_name].c
*/

int					builtin_exit(t_env **env, char **args);
int					builtin_cd(t_env **env, char **args);
int					try_cd_l(t_env **env, char *path);
int					try_cd_p(t_env **env, char *path);
int					builtin_env(t_env **env, char **args);
int					builtin_setenv(t_env **env, char **args);
int					builtin_unsetenv(t_env **env, char **args);
int					builtin_echo(t_env **env, char **args);
int					builtin_which(t_env **env, char **args);
int					builtin_procs(t_env **env, char **args);
int					builtin_fg(t_env **env, char **args);

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

void				add_word(t_token token, char *str, t_word **wordlist);
void				lex_analysis(char *cmdline, t_word **wordlist,
		char **errmsg);
void				lex_semicol_word(char *cmdline, t_word **wordlist,
		t_lexdata *lexdata, char **errmsg);
void				lex_space_word(char *cmdline, t_word **wordlist,
		t_lexdata *lexdata, char **errmsg);
void				lex_amp_and_word(char *cmdline, t_word **wordlist,
		t_lexdata *lexdata, char **errmsg);
void				lex_pipe_or_word(char *cmdline, t_word **wordlist,
		t_lexdata *lexdata, char **errmsg);
void				lex_shift_src_redirect(char *cmdline, t_word **wordlist,
		t_lexdata *lexdata, char **errmsg);
void				lex_shift_dest_redirect(char *cmdline, t_word **wordlist,
		t_lexdata *lexdata, char **errmsg);
void				lex_rshift_word(char *cmdline, t_word **wordlist,
		t_lexdata *lexdata, char **errmsg);
void				lex_lshift_word(char *cmdline, t_word **wordlist,
		t_lexdata *lexdata, char **errmsg);
void    lex_tilde_exp(char *cmdline, t_lexdata *lexdata, char **errmsg);
void    lex_dollar_exp(char *cmdline, t_lexdata *lexdata, char **errmsg);

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
void				delete_redirects(t_redirect *redirs);

/*
** redirections.c
*/

void				add_redirect(t_redirect **redirs,
		char *left, char *right, t_token token);
int					analyze_redirects(t_word **arglist,
		t_redirect **redirs, char **errmsg);

/*
** redirections_apply.c, redirections_apply_[token].c
*/

int					open_file_fd(char *filename, int mode,
		int append, char **errmsg);
int					apply_redirects(t_redirect *redirs,
		int *fdtmp_array, int *fdsave_array, char **errmsg);
int					apply_redirect_pipe(t_redirect *redir,
		int *fdtmp_array, int *fdsave_array, char **errmsg);
int					apply_redirect_lshift(t_redirect *redir,
		int *fdtmp_array, int *fdsave_array, char **errmsg);
int					apply_redirect_lshift_amp(t_redirect *redir,
		int *fdtmp_array, int *fdsave_array, char **errmsg);
int					apply_redirect_rshift(t_redirect *redir,
		int *fdtmp_array, int *fdsave_array, char **errmsg);
int					apply_redirect_rshift_amp(t_redirect *redir,
		int *fdtmp_array, int *fdsave_array, char **errmsg);
int					apply_redirect_rshift2(t_redirect *redir,
		int *fdtmp_array, int *fdsave_array, char **errmsg);

/*
** interpreter.c, interpreter_[token].c
*/

int					exec_ast(t_ast *node, int *pipein, int *pipeout);
int					exec_ast_semicol(t_ast *node, int *pipein, int *pipeout);
int					exec_ast_or(t_ast *node, int *pipein, int *pipeout);
int					exec_ast_and(t_ast *node, int *pipein, int *pipeout);
int					exec_ast_pipe(t_ast *node, int *pipein, int *pipeout);
int					exec_ast_arg(t_ast *node, int *pipein, int *pipeout);

/*
** signals.c
*/

void				sighandler(int signo);
void				reset_sighandlers(void);
void				ignore_signals(void);

/*
** termdata.c
*/

void				init_termdata(t_termdata *termdata);
void				go_forward(t_termdata *termdata);
void				go_backward(t_termdata *termdata);
void				restore_pos(t_termdata *termdata);

/*
** input.c
*/

void				clear_cmd(t_termdata *termdata);
void				print_cmd(char *cmd, t_termdata *termdata);
void				add_to_input(char *cmd, size_t	*cur, t_termdata *termdata, char *keybuff);
char				*ask_for_input(void);

/*
** input_actions.c
*/

void				perform_actions(char *cmd, size_t *cur, t_termdata *termdata, char *keybuff);

/*
** input_actions_[action].c
*/

void				input_action_delete(char *cmd, size_t *cur, t_termdata *termdata);
void				input_action_arrowright(char *cmd, size_t *cur, t_termdata *termdata);
void				input_action_arrowleft(char *cmd, size_t *cur, t_termdata *termdata);
void				input_action_shiftarrowright(char *cmd, size_t *cur, t_termdata *termdata);
void				input_action_shiftarrowleft(char *cmd, size_t *cur, t_termdata *termdata);
void				input_action_shiftarrowup(char *cmd, size_t *cur, t_termdata *termdata);
void				input_action_shiftarrowdown(char *cmd, size_t *cur, t_termdata *termdata);
void				input_action_home(char *cmd, size_t *cur, t_termdata *termdata);
void				input_action_end(char *cmd, size_t *cur, t_termdata *termdata);
void				input_action_shifthome(char *cmd, size_t *cur, t_termdata *termdata);
void				input_action_shiftend(char *cmd, size_t *cur, t_termdata *termdata);

/*
** output.c
*/

int					print_prompt(t_env **env);
void				print_sig_error(int sig);
void				print_chdir_error(char *path);

/*
** pipe.c
*/

void				add_proc_to_pipe(t_process *proc);
int					wait_pipe(void);

/*
** process.c
*/

t_process			*new_process(void);
t_process			*copy_processes(t_process *src);
void                delete_processes(t_process *procs);

/*
** process_control.c
*/

pid_t				restore_process(void);
int					post_process(t_process *proc, int status);

/*
** path.c
*/

char				*find_cmd_path(t_env **env, t_env **cmd_env, char *cmd);

/*
** history.c
*/

void				add_history_elem(t_history **history, char *cmd);
void				delete_history(t_history *history);

/*
** init.c, init_[feature].c
*/

void				init(t_env **env, char **envp);
void                init_shell(void);
void                init_signals(void);
void				init_env(t_env **env, char **envp);
void				init_builtins(void);

/*
** starter.c
*/

int					start_command(t_env **env,
		t_env **cmd_env, t_process *proc);

/*
** starter_process.c
*/

int					start_process(t_env **env, t_process *proc);

#endif
