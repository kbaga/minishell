/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romeo <romeo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:27:20 by kbaga             #+#    #+#             */
/*   Updated: 2025/01/02 12:18:19 by romeo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*-------- SYSTEM HEADERS --------*/
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sysexits.h>
# include <unistd.h>
# include <limits.h>
# include "../libft/libft.h"

/*---------- MACROS --------------------------*/
# define PROMPT "minishell >"
# define ERR_SYN_PIPE "Syntax error: pipes\n"
# define FAIL_SYSCALL -1
# define OKAY 0
# define FAIL_SYSCALL_PARENT 1
# define FAIL_SYSCALL_CHILD 2

/*-------- GLOBAL VARIABLES ------------------*/
extern int g_exit_status;

/*---------- ENUMS ---------------------------*/
typedef enum s_token
{
	COMMAND,
	PIPE,
	TRUNCATE,
	APPEND,
	REDIRECT_INPUT,
	HEREDOC,
}	t_token;

/*---------- STRUCTS -------------------------*/

/* Lexer List */
typedef struct s_lexer_list
{
	char				*str;
	t_token				type;
	int					index;
	int					is_command;
	struct s_lexer_list	*prev;
	struct s_lexer_list	*next;
}	t_lx;

/* AST Node */
typedef struct s_ast_node
{
	t_token				type;
	char				*command;
	char				**args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

/* Expander */
typedef struct s_exp
{
	char	*begining;
	char	*res;
	char	*invalid;
	char	*env_val;
	char	*var;
	char	*str;
	char	*conv;
	int		pos;
	int		len;
	int		recently_invalid;
	int		expanded;
	int		flag;
}	t_exp;

/* Environment List */
typedef struct s_env_node
{
	char				*key;
	char				*val;
	struct s_env_node	*next;
}	t_env_node;

typedef struct s_env_list
{
	t_env_node	*head;
}	t_env;

typedef struct s_pid_list {
    pid_t *pids;
    size_t count;
    size_t capacity;
} t_pid_list;

/* Shell State */
typedef struct s_shell
{
	char			*rl_input;
	char			*rl_copy;
	int				exit_status;
	t_env			*environ;
	t_lx			*lex_head;
	struct s_exec	*executor;
	t_pid_list		*pid_list;
}	t_shell;

/* Exec Node */
typedef struct s_exec
{
	int				id;
	int				size;
	int				fd_in;
	int				fd_out;
	int				trunc;
	int				append;
	int				redir_input;
	int				heredoc;
	char			**execs;
	struct s_exec	*prev;
	struct s_exec	*next;
	int				pipe;
}	t_exec;

/* Exec Context */
typedef struct s_exec_context
{
	t_lx	*current_lexer;
	t_exec			*exec_head;
	t_exec			*current_exec;
	t_lx			*lex_head;
	t_exec			*exec_tail;
	int				lex_id;
	int				exec_id;
	int				fd_pipe;
}t_exec_context;

typedef struct s_fd_backup
{
    int saved_stdin;
    int saved_stdout;
} t_fd_backup;


/*-----------------FD--------------*/
void restore_fds(t_fd_backup *backup);
t_fd_backup save_fds(void);



/* -------- EXPANDER FUNCTIONS -------- */
char            *realloc_str(char *res, int pos);
int             handle_var(t_shell *shell, t_exp *exp, int i);
int             skip_single_quote(char *str, int i, t_exp *exp);
int             skip_double_quote(t_shell *shell, char *str, int i, t_exp *exp);

/* -------- EXPORT FUNCTIONS -------- */
int             equal_pos(char *s);

/* -------- ARRAY UTILS -------- */
int             is_token2(char to_check);
char            *add_substr(char *str, int i, int k);
int             proc_tok(char **arr, char *s, int *i, int *j);
int             proc_inp(char **arr, char *s);

/* -------- SORT FUNCTIONS -------- */
int             count_env_nodes(t_env *env);

/* -------- FREER FUNCTIONS -------- */
void            free_tab(char **tab);
t_lx            *free_lex(t_lx *lex_head);


/* Info Struct */
typedef struct s_info
{
	int		wstatus;
	t_shell	*shell;
	int		stdin_cpy;
	pid_t	*pids;
}	t_info;

/* Key-Value Pair */
typedef struct s_pair
{
	char	*key;
	char	*val;
}	t_pair;

/* Token Context */
typedef struct s_token_ctx
{
	char	**arr;
	char	*s;
	int		arr_size;
	int		index;
}	t_token_ctx;

/*---------- FUNCTION PROTOTYPES -------------*/


///////////       RANDOMS              ///////////

t_exp			*init_exp(char *str);
void			free_exp(t_exp *exp);
int				handle_char(t_exp *exp, char c);
char			*ft_join_exp(char *s1, char *s2);
int				is_valid(char *arg);
int				ext_val(char *arg, t_env_node *node);
void			node_free(t_env_node *node);
char			*ft_join_char(char *s, char c);
int				expand_var(t_shell *shell, char **s, t_exp *exp, int i);
int				is_valid_id(char *arg);
int				create_add(t_shell *shell, char *args);
int				exp_no_args(t_env *env);
char			*ext_key(char *str, int *pos);
void			existing_node(t_env_node *node, char *arg, int pos);
void			new_node(t_env *env, char *key, char *arg, int pos);

/* -------- EXPANDER FUNCTIONS -------- */
char            *realloc_str(char *res, int pos);
int             handle_var(t_shell *shell, t_exp *exp, int i);
int             skip_single_quote(char *str, int i, t_exp *exp);
int             skip_double_quote(t_shell *shell, char *str, int i, t_exp *exp);

/* -------- EXPORT FUNCTIONS -------- */
int             equal_pos(char *s);

/* -------- ARRAY UTILS -------- */
int             is_token2(char to_check);
char            *add_substr(char *str, int i, int k);
int             proc_tok(char **arr, char *s, int *i, int *j);
int             proc_inp(char **arr, char *s);

/* -------- SORT FUNCTIONS -------- */
int             count_env_nodes(t_env *env);

/* -------- FREER FUNCTIONS -------- */
void            free_tab(char **tab);
t_lx            *free_lex(t_lx *lex_head);



/* Initialization */
t_shell			*init_shell(char **envp);

/* Token Functions */
t_token			assign_type(char tok);
t_lx			*create_lexer_list(char **input_array);
t_lx			*fill_lexer_list(char **input_array);
t_lx			*tokenize(t_shell *shell);
t_lx			*create_token(char **array, t_lx *curr, int i);
t_token			which_type(char *s);

int				is_token(char *str);

/* Parsing Functions */
int				check_pipe(t_lx *lexer);
int				parser(t_shell *shell);
int				count_el(char *rl_copy);
t_lx	*lexer(t_shell *shell);
char			**create_arr(t_shell *shell);
int				pars_check(char *str);

void			free_arr(char **arr, int size);
int				process_token(t_token_ctx *ctx, int *i);

/* Builtins */
int				is_builtin(const char *command);
void			ft_cd(char **args);
//void			ft_echo(char **args);
void			ft_echo(char **execs, t_shell *shell); ///kenny
void			ft_env(t_env_node *env);
void			ft_exit(t_shell *shell, char **args);

void			ft_pwd(void);
void			ft_export(char **args);
int				unset(t_shell *shell, char **execs);
void			execute_builtin(t_shell *shell, t_exec *cmd);
void			handle_builtin(t_shell *shell, t_exec *exec_node);
void			exporting(t_shell *shell, char *str);

/* Execution */
t_exec			*create_exec_list(t_shell *shell);
char			**tab_command(t_exec_context *context);
void			execute_command(t_exec *node, t_env *env_list);
void			fork_external(t_shell *shell, t_exec *head, t_env *env_list);
void			fork_builtin(t_shell *shell, t_exec *head, t_env *env_list);
void			send_to_exec(t_shell *shell, t_exec *cmd, t_env *env_list);
void			execute_exec_list(t_shell *shell, t_exec *cmd_list, t_env *env);
void			error_command(const char *message);
void			command_not_found(const char *cmd);

/*          PID PROCESS MANIPULATION        */


t_pid_list	*init_pid_list(void);
void		add_pid(t_pid_list *list, pid_t pid);
void		wait_all_pids(t_pid_list *list);
void		free_pid_list(t_pid_list *list);


/* Redirection */
void			handle_redirection(t_shell *shell, t_exec_context *context);
void			handle_truncate_redirection(t_exec *node, t_lx *current);
void			handle_append_redirection(t_exec *node, t_lx *current);
void			handle_input_redirection(t_exec *node, t_lx *current);
void			handle_heredoc_redirection(t_exec *node, t_lx *current);
void 			link_exec_with_pipe(t_exec *node_exec, t_exec_context *context);
int				is_delimiter(const char *buffer, const char *delimiter);
void			int_to_string(int n, char *buffer, size_t size);

char			*clean_rl(char *rl_copy);
t_env			*init_env(char **envp);
char			**input_split(const char *s);
t_shell			*init_shell(char **envp);

/* Environment */
t_env_node		*get_node(t_env *env, char *key);
t_env_node		*create_node(char *var);
t_env_node		*add_node(t_env *env, t_env_node *node);
char			*my_getenv(char *name, t_env *env_list);
void			free_env(t_env *env);
void			free_env_list(t_env *env_list);

/* Utils */
t_lx			*lexer_clean(t_shell *shell, t_lx *lex_head);
void			reset_shell(t_shell *shell);
void			handle_line(t_shell *shell, char *line);
char			*interpolate(t_shell *shell, char *str);
void			interpolate_tokens(t_shell *shell);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strjoin2(char const *s1, char const *s2);
char			**ft_split(char const *s, char c);
void			ft_free_tab(char **tab);
void			no_delim_found(char *str, int *len);
void			free_exec_list(t_exec *head);
void			free_exec_node(t_exec *node);

/* Safe Functions */
void			*safe_malloc(size_t bytes);
void			ft_reset_std(t_exec *data);
void			error_exit(const char *msg);
void			safe_pid(pid_t pid);
void			safe_pipe(int pipefd[2]);

/* Sorting */
t_pair			*create_env_array(t_env *env, int count);
void			sort_env_array(t_pair *pairs, int count);
void			print_env_array(t_pair *pairs, int count);
void			free_env_arr(t_pair *pairs, int count);

/* Free Functions */
void			free_exec_node2(t_exec *node);
void			free_exec(t_exec *list);
void			free_heap(t_shell *shell);

/* Signals */
void			ft_signal(int sig);

#endif
