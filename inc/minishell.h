/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:56:01 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/10 01:01:48 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE

#include <fcntl.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define USAGE_ERROR "Correct use: ./minishell\n"
#define READ_FD 0
#define WRITE_FD 1

//* Types of tokens, used to create the AST in the parser.
typedef enum token_type
{
	TOKEN_STRING,
	TOKEN_PIPE,
	TOKEN_OUTPUT,
	TOKEN_INPUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
}					t_token_type;

/*
 *	Automaton's alphabet, each symbol represents one column in
 *	the DFA's transition table.
 */
typedef enum input
{
	INPUT_SPACE,
	INPUT_PIPE,
	INPUT_LESS,
	INPUT_GREATER,
	INPUT_DOUBLE_QUOTE,
	INPUT_SINGLE_QUOTE,
	INPUT_ELSE
}					t_input;

typedef enum t_redirect_type
{
	APPEND,
	WRITE,
	INFILE,
	HEREDOC
}					t_redirect_type;

/*
 * Structure used to create the Abstract Syntax Tree (AST).
 * It holds the data and two pointers to each of its children.
 */
typedef struct s_ast
{
	void			*data;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

typedef struct redirect_file
{
	char			*value;
	t_redirect_type	type;
}					t_redirect_file;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/*
 * Structure representing a token.
 * Each token holds a string value, a type, and a pointer to the next
 * token in the list.
 */
typedef struct s_token
{
	char			*full_cmd;
	char			*flags;
	char			*cmd;
	char			*args;
	t_token_type	type;
	t_list			*infiles;
	t_list			*outfiles;
	struct s_token	*next;
}					t_token;

/*
 *	Each of the lexer's variables:
 *
 *		- Tokens: Array of tokens returned to create the Abstract Syntax Tree.
 *		- Buffer: Used for each of the tokens. It's limited to 256 due to the
 * 		filename length limits of most Unix file systems.
 *		- Automaton status: Stores the value returned by the transition table.
 */
typedef struct s_lexer
{
	t_token			*tokens;
	char			*buf;
	int				automaton_status;
}					t_lexer;

typedef struct s_params
{
	int				fd[2];
	int				pid;
	int				total_cmds;
	int				pid_right;
	int				pid_left;
	int				status;
	char			*cmd_path;
	char			**cmd_exec;
	char			**env;	
}					t_params;

typedef struct t_kv
{
	char			**keys;
	char			**values;
}					t_kv;

/*
 * The environment translated into a linked list.
 * It has three variables:
 *	- Key: Variable's name.
 *	- Value: Variable's value.
 *	- A pointer to the next env variable.
 */
typedef struct s_env
{
	char			*key;
	char			*value;
	int				hide;
	struct s_env	*next;
}					t_env;

typedef struct s_counters
{
	int				i;
	int				j;
	int				k;
}					t_counters;

extern int			g_exit_status;

void				create_env_null(t_env **env);
void				before_create_env(t_env **env, char **envp);
void				create_env(t_env *env, char **envp);
void				handle_input(t_env *env, char *input);

t_token				*lexer(char *line);
void				lexer_init(t_lexer *lexer);
int					transition_table(int i, int j);
int					get_symbol(char c);

// UTILS
void				*ft_memset(void *b, int c, size_t len);
void				skip_input_spaces(char **input);
char				*skip_args_spaces(char *args);
void				skip_spaces(char *str, int *i);
int					ft_charcmp(char c1, char c2);
void				ft_bzero(void *s, size_t n);
char				ft_lstlastchar(t_token *lst);
size_t				ft_strlen(const char *str);
int					ft_strcmp(const char *str1, const char *str2);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strchr(const char *s, int c);
int					findchar(const char *s, int c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					n_words(char const *s, char c);
char				**split_formated(char *s, char c);
size_t				ft_newstrlcpy(char *dst, char *src, size_t size);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strjoin_cmd(char *s1, char *s2);
size_t				ft_strlcpy(char *dst, char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
void				ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				**free_matrix(char **str);
void				free_tokens(t_token *token);
void				free_env(t_env *env);
void				free_ast(t_ast *node);
void				free_variable(t_env *node);
char				*ft_str_toupper(char *str);
char				**ft_split(char const *s, char c);
char				*ft_strdup(const char *s);
t_env				*new_node(char *key, char *value, int hide);
void				add_bottom(t_env **env, t_env *new_envi);
void				remove_node(t_env **env, char *key);
int					is_alpha(char c);
int					is_number(char c);
int					is_alnum(char c);
int					is_valid(char *str);
int					ft_count_words(char **strs);
int					skip_quoted_string(char *str, int counter);
char				*get_unquoted_str(char *str);
char				*get_quoted_str(char *str, char quote);
int					ft_isspace(char c);
char				*trim_sp(const char *str);
char				*append_str(char *base, char *suffix);
char				*remove_substr(char *substr, char *old_str);
int					valid_char_filename(char c);
char				*get_next_word(char *cmd, char *str, int caller);
int					count_words_smart(const char *input);
char				**smart_split(const char *input);
int					ft_atoi(const char *str);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_realloc(void *ptr, size_t new_size);
char				*ft_strcat(char *dest, const char *src);
char				*ft_str(long aux, long size, long n1, int n);

// BUILT_INS
int					flags_validator(char *flags, char *command_flags);
void				build_switch(t_env *env, t_ast *ast, t_token *tokens);
void				update_pwd(char *pwd_key, t_env **env, char *new_pwd);
void				command_pwd(t_token *tokens);
void				command_env(t_token *tokens, t_env *env);
void				cd_actions(t_token *tokens, t_env *env);
void				command_cd(t_token *token, t_env *env);
char				*get_content_var(char *str);
void				handle_variable_export(char *var, t_env *env);
char				*get_var(char *str);
void				command_export(t_token *tokens, t_env *envi);
void				print_env(t_env *envi, int flag);
void				command_unset(t_token *tokens, t_env *env);
void				command_echo(t_token *tokens);
void				command_clear(t_token *tokens);
int					validate_export(char *key, char *value);
void				unset_actions(t_token *tokens, t_env *env);
int					is_option_n(char *str);
char				*ft_itoa(int n);
int					count_quotes(char *str);
void				handle_cd_flags(t_token *tokens);
void				handle_env_flags(t_token *tokens);
void				handle_unset_flags(t_token *tokens);
char				*path_error(void);

// FT_MALLOC
void				*ft_malloc(size_t size);

// TOKENIZER
void				tokenize_strings(t_lexer *lexer, t_token_type type,
						char **input);
void				tokenizer(t_lexer *lexer, char **input);
void				add_token(t_token **head, t_token *new_token);
t_token				*create_token(t_token_type type, char *value);
void				get_redirections(t_token *token);
void				get_cmd_flags_and_args(t_token *token, char *full_cmd);

// PARSER
void				build_tree(t_token *tokens, t_ast **current_node);
t_ast				*parsing(t_token *tokens, t_env *env);
t_ast				*create_node(void *data);
int					count_ast_nodes(t_ast *node);

// SIGNALS
void				handle_signals(void);
void				signals_handler(int sig);
void				signals_handler_for_blockers(int sig);
void				son_signal(void);
void				sigint_handler(int sig);

// EXPANDER
void				expander(t_token **tokens, t_env *env);
char				*expand_token(t_token *token, t_kv kv, int size);
char				**get_keys(char *str, int keys_nbr);
char				**get_values(t_env *env, char **keys, int *keys_nbr);
int					get_nbr_of_keys(char *str);
int					ft_strlen_v2(char **strs);
int					copy_len(const char *s);
char				*remove_double_quotes(char *str);
char				*get_command(char *full_cmd);
int					get_word_len(char *full_cmd, int i);

// REMOVE QUOTES
char				*remove_quotes(char *str);

// PIPES
void				get_path(char **env, t_params *p, t_token *t);
int					have_path(char **env);
int					have_redirection(t_token *token);
int					tramited(char *path, t_params *p, t_token *t);
void				execute_cmd(t_params *p);
void				init_execute(t_token *data, t_params *p);
void				handle_pipe(t_ast *node, t_params *p, t_env *env);
void				wait_for_child(int pid, t_params *p);
int					is_priority_command(t_token *data);
void				pipes_and_execute(t_ast *node, t_params *p, t_env *env,
						t_token *data);
void				execute_node(t_ast *node, t_params *p, t_env *env);
void				execute_ast(t_ast *node, t_params *p, \
					t_env *env, int prev_fd);
char				*create_char(t_env *env);
int					count_env_nodes(t_env *env);
char				**init_env(t_env *env);
char				*access_absolute(char *path);
char				*access_validate(char **path, char *comand);
void				validate_comand(char **comand_splited);
char				*command_with_space(char *comand);
char				*load_param(char **path, char *comand);
void				before_execute(t_ast *node, t_params *p, t_env *env);
int					handle_redirection(t_ast *node);
int					is_builtin(char *cmd);
int					redirect_append(t_ast *ast);
int					create_heredoc_file(char **temp_filename);
void				process_heredocs_in_ast(t_ast *node, t_env *env);
char				*get_env_value(const char *key, char **environ);
void				write_to_heredoc(int fd_file, char *buffer, t_env *env);
char				*get_env_value_heredoc(t_env *env, const char *key);
char				*expand_buffer(char *result, size_t *buf_size, \
					size_t required_size);
char				*expand_variable_heredoc(const char **p, t_env *env, \
					char *result, size_t *buf_size);
void				heredoc_signals_handler(int sig);
int					redirect_input(t_ast *ast);
int					redirect_output(t_ast *ast);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				exit_program(t_env *env, t_ast *ast, t_token *tokens);
void				handle_command(char *cleaned, t_token *tokens, t_env *env,
						t_ast *ast);
void				create_pipe_processes(t_ast *node, t_params *p, \
					t_env *env, int in_fd);
char				*expand_variables_heredoc(const char *line, t_env *env);
void				execute_pipe_ast(t_ast *node, t_params *p, \
					t_env *env, int in_fd);
