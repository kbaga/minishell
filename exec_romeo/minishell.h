/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romeo <romeo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:27:20 by kbaga             #+#    #+#             */
/*   Updated: 2024/11/20 18:10:20 by romeo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
//# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sysexits.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
//# include "../libft/libft.h"

/*----------MACROS-----------------------------*/

/*-----Struct pour la grammaire et Lexer-------*/

typedef enum	s_token
{
	COMMAND,
	PIPE, // |
	TRUNCATE, // >
	APPEND, //>>
	REDIRECT_INPUT, //<
	HEREDOC, //<<
}	t_token;

typedef struct	s_lexer_list
{
	char				*str;
	t_token				type;
	int					index;
	int					is_command;
	struct s_lexer_list	*prev;
	struct s_lexer_list	*next;
}	t_lexer_list;

typedef struct	s_ast_node
{
	t_token				type;
	char				*command;
	char				**args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

/*-------- Struct utiles pour expander-------------*/

typedef struct	s_expander
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
} t_expander;

typedef struct	s_env_list
{
	struct s_env_node	*head;
}	t_env_list;

/* Struct qui definit un node qui detient les variable d'env
la clef peut etre HOME PATH USER, a cela on assignera une 
 valeur HOME -> /home/username
*/
typedef struct	s_env_node
{
	char	*key;
	char	*val;
	struct s_env_node	*next;
}	t_env_node;


/*----------------------------------------------------------------------------------------*/
/*------------------------EXECUTION-------------------------------------------------------*/
/*----------------------------------------------------------------------------------------*/

typedef struct	s_shell
{
	char	*rl_input; //Saisi du User dans le terminal
	char	*rl_copy; //On conserve une copie au cas pour l'historique
	struct s_env_list	*environ;
	struct s_lexer_list	*lex_head;//premier de la liste des tokens
	struct s_exec	*exec; //infos necessaires pour exec cmd
}	t_shell;

typedef struct	s_info
{
	int		wstatus;
	t_shell	*shell;
	int		stdin_cpy;
	pid_t	*pids;
}	t_info;

typedef struct	s_exec
{
	int		id;
	int		size;
	int		fd_in;
	int		fd_out;
	int		trunc;
	int		append;
	int		redir_input;
	int		heredoc;
	char	**path;
	char	**execs;
	struct s_exec	*prev;
	struct s_exec	*next;
}	t_exec;

/*--------- TOKEN FUNC--------*/
t_token			assign_type(char tok);
t_lexer_list	*create_lexer_list(char **input_array);
t_lexer_list	*fill_lexer_list(char **input_array);
t_lexer_list	*tokenize(t_shell *shell);
t_token			which_type(char *s);

/*----- PARSING FUNCTIONS ------*/
char	**input_split(const char *s);

/*------- SAFE FUNCTIONS ------*/\
void	*safe_malloc(size_t bytes);
void	ft_reset_std(t_exec *data);
void	error_exit(const char *msg);
void	safe_pid(pid_t pid);
void	safe_pipe(int pipefd[2]);

/*------ UTILS FUNCTIONS -----*/
int		ischar(char c);

///////////////////////////////////////////////////////////////////////////////////////////////////////

/*--------- BUILT-IN COMMANDS ----------------*/
int		is_builtin(const char *command);
int		ft_cd(char **args);
int		ft_echo(char **args);
int		ft_env(t_env_node *env);
int		ft_exit(char **args);
int		ft_pwd(void);
int		ft_export(char **args);
int		ft_unset(char **args);

/*---------- EXECUTION -----------------------*/
t_exec	*create_exec_node(int id, char **cmd);
void	link_exec_with_pipe(t_exec *left, t_exec *right);
void	execute_command(t_exec *node, t_env_list *env_list);
void	fork_external(t_exec *head, t_env_list *env_list);
void	send_to_exec(t_exec *cmd, t_env_list *env_list);
void	execute_exec_list(t_exec *cmd_list, t_env_list *env);

/*--------- REDIRECTION FUNCTIONS ------------*/
void	handle_truncate_redirection(t_exec *node, t_lexer_list *current);
void	handle_append_redirection(t_exec *node, t_lexer_list *current);
void	handle_input_redirection(t_exec *node, t_lexer_list *current);
void	handle_heredoc_redirection(t_exec *node, t_lexer_list *current);
void	handle_redirection(t_exec *node, t_lexer_list *current);

/*--------- HEREDOC FUNCTIONS ----------------*/
int		read_heredoc_content(const char *delimiter, int fd);
void	setup_heredoc_redirection(t_exec *node, const char *tmp_filename);
int		create_temp_file(char *filename, size_t size, int *fd);
int		is_delimiter(const char *buffer, const char *delimiter);

/*--------- ENVIRONMENT UTILS ----------------*/
char	*my_getenv(char *name, t_env_list *env_list);
void	free_env_list(t_env_list *env_list);

/*--------- UTILS ----------------------------*/
size_t	ft_strlen(const char *c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(const char *s1, const char *s2);
int		ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);
void	ft_free_tab(char **tab);
char	*ft_itoa(int n);
void	int_to_string(int n, char *buffer, size_t size);
void	error_command(const char *message);
void	command_not_found(const char *cmd);

#endif
