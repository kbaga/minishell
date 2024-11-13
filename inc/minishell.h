/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaga <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:27:20 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/11 19:52:27 by kbaga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sysexits.h>
# include <unistd.h>
# include "../libft/libft.h"

/*----------MACROS-----------------------------*/
# define PROMPT "minishell >"
/*-----Struct pour la grammaire et Lexer-------*/

typedef enum s_token
{
	COMMAND,
	PIPE,
	TRUNCATE,
	APPEND,
	REDIRECT_INPUT,
	HEREDOC,
}	t_token;

typedef struct s_lexer_list	t_lx;

struct s_lexer_list
{
	char				*str;
	t_token				type;
	int					index;
	int					is_command;
	struct s_lexer_list	*prev;
	struct s_lexer_list	*next;
};

typedef struct s_ast_node
{
	t_token				type;
	char				*command;
	char				**args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

/*-------- Struct utiles pour expander-------------*/

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
	char			**path;
	char			**execs;
	struct s_exec	*prev;
	struct s_exec	*next;
}	t_exec;

//Variable Globale

typedef struct s_shell
{
	char						*rl_input;
	char						*rl_copy;
	t_env						*environ;
	struct s_lexer_list			*lex_head;
	t_exec						*executor;
}	t_shell;

typedef struct s_info
{
	int		wstatus;
	t_shell	*shell;
	int		stdin_cpy;
	pid_t	*pids;
}	t_info;

/*-------- TOKEN FUNC--------*/
t_token			assign_type(char tok);
t_lx			*create_lexer_list(char **input_array);
t_lx			*fill_lexer_list(char **input_array);
t_lx			*tokenize(t_shell *shell);
t_lx			*create_token(char **array, t_lx *curr, int i);
t_token			which_type(char *s);

/*----- PARSING FUNCTIONS ------*/
char			**input_split(const char *s);
int				check_pipe(t_lx *lexer);
int				parser(t_shell *shell);
t_lx			*lexer(t_shell *shell);

/*------PARSING UTILS ------*/
int				pars_check(char *str);
int				get_type(const char *str);
int				ft_isspace(int c);
char			*clean_str(char *rl_copy, size_t start, size_t end);
char			*clean_rl(char *rl_copy);

/*------TOKEN FUNCTIONS------*/

/*------EXPANDER FUNCTIONS----*/
char			*realloc_str(char *res, int pos);
t_exp			*init_exp(char *str);
char			*ft_join_exp(char *s1, char *s2);
char			*ft_join_char(char *s, char c);
void			free_exp(t_exp *exp);
int				expand_var(t_shell *shell, char **s, t_exp *exp, int i);
int				handle_var(t_shell *shell, t_exp *exp, int i);
int				handle_char(t_exp *exp, char c);

/*----- EXPORT FUNCTIONS --- */

t_env_node		*get_node(t_env *env, char *key);
t_env_node		*create_node(char *var);
t_env_node		*add_node(t_env *env, t_env_node *node);
int				is_valid(char *arg);
int				is_valid_id(char *arg);
void			node_free(t_env_node *node);
int				ext_val(char *arg, t_env_node *node);
int				create_add(t_shell *shell, char *args);
void			free_env(t_env *env);
void			new_node(t_env *env, char *key, char *arg, int pos);
void			existing_node(t_env_node *node, char *arg, int pos);
int				exp_no_args(t_shell *shell);
char			*ext_key(char *str, int *pos);
int				equal_pos(char *s);
int				unset(t_shell *shell, char **args);

/*------ARRAY UTILS ---------*/
void			no_delim_found(char *str, int *len);
int				is_token(char to_check);
int				is_token2(char to_check);
char			*add_substr(char *str, int i, int k);
int				proc_tok(char **arr, char *s, int *i, int *j);
int				proc_inp(char **arr, char *s);

/*------- SAFE FUNCTIONS ------*/
void			*safe_malloc(size_t bytes);
void			ft_reset_std(t_exec *data);
void			error_exit(const char *msg);
void			safe_pid(pid_t pid);
void			safe_pipe(int pipefd[2]);

/*------ UTILS FUNCTIONS -----*/

/*------ FREER FUNCTIONS ------*/
void			free_env(t_env *env);
void			free_exec(t_exec *list);
void			free_heap(t_shell *shell);
void			free_tab(char **tab);
t_lx			*free_lex(t_lx *lex_head);

#endif
