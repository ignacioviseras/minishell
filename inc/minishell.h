/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:56:01 by drestrep          #+#    #+#             */
/*   Updated: 2024/11/12 13:02:58 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdint.h>
#include <readline/readline.h>
#include <readline/history.h>

#define USAGE_ERROR "Correct use: ./minishell\n"

# ifndef READ_END
#  define READ_END 0
# endif

# ifndef WRITE_END
#  define WRITE_END 1
# endif

//* Types of tokens, used to create the AST in the parser.
typedef enum token_type
{
	TOKEN_STRING,
	TOKEN_PIPE,
	TOKEN_OUTPUT,
	TOKEN_INPUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
}			token_type;

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
} 			input;

/*
 * Structure used to create the Abstract Syntax Tree (AST).
 * It holds the data and two pointers to each of its children.
 */
typedef struct s_ast
{
	void			*data;
	struct s_ast	*left;
	struct s_ast	*right;
}				t_ast;

/*
 * Structure representing a token.
 * Each token holds a string value, a type, and a pointer to the next
 * token in the list.
 */
typedef struct s_token
{
	char			*cmd_args;
	char			*flags;
	char			*cmd;
	char			*args;
	token_type		type;
	struct s_token	*next;
}				t_token;

/* 
 *	Each of the automaton's variables:
 
 *	 - Tokens: Array of tokens returned to create the Abstract Syntax Tree.
 *	 - Buffer: Used for each of the tokens. It's limited to 256 due to the
 * 	   filename length limits of most Unix file systems.
 *	 - Status: Stores the value returned by the transition table.
 */
typedef struct s_automata
{
	t_token			*tokens;
	char			buf[256];
	int				status;
}				t_automata;

typedef struct s_params
{
	char		*file1;
	char		*file2;
	char		*comand_path1;
	char		*comand_path2;
	char		**comand1;
	char		**comand2;

}			t_params;


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
}				t_env;

void				create_env(t_env *env, char **envp);
void				handle_input(t_env *env, char *input);

t_token				*lexer(char *line);
void				automata_init(t_automata *automata);
int					transition_table(int i, int j);
int					get_symbol(char c);

// UTILS		
void				*ft_memset(void *b, int c, size_t len);
void				skip_spaces(char **input);
int					ft_charcmp(char c1, char c2);
void				ft_bzero(void *s, size_t n);
char				ft_lstlastchar(t_token *lst);
size_t				ft_strlen(const char *str);
int					ft_strcmp(const char *str1, const char *str2);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strchr(const char *s, int c);
int					ft_charseach(const char *s, int c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					n_words(char const *s, char c);
char				**split_formated(char const *s, char c);
char				*ft_strjoin(char *s1, char *s2);
size_t				ft_strlcpy(char *dst, char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
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



//BUILT_INS
int					flags_validator(char *flags, char *command_flags);
void				build_switch(t_env *env, t_ast *ast, t_token *tokens);
char				*env_finder(t_env **env, char *find);
void				command_pwd(t_token *tokens);
void				command_env(t_token *tokens, t_env *env);
void				cd_actions(t_token *tokens);
void				command_cd(t_token *token);
char				*get_content_var(char *str);
char				*get_value(t_env **envi, char *find);
char				*get_var(char *str);
void				command_export(t_token *tokens, t_env *envi);
char				*get_home(char *pwd);
void				print_env(t_env *envi, int flag);
void				command_unset(t_token *tokens, t_env *env);
void				command_echo(t_token *tokens);
void				command_clear(t_token *tokens);
void				print_echo(char *input);
void				export_actions(t_token *tokens, t_env *env);
int					validate_export(char *key, char *value);
void				unset_actions(t_token *tokens, t_env *env);
int					is_option_n(char *str);


// FT_MALLOC
void				*ft_malloc(size_t size);

// TOKENIZER		
void				tokenize_strings(t_automata *automata, char **input);
void				tokenizer(t_automata *automata, char **input);
void				add_token(t_token **head, t_token *new_token);
t_token				*create_token(token_type type, char *value);

// PARSER
void				build_tree(t_token *tokens, t_ast **current_node);
t_ast				*parsing(t_token *tokens, t_env *env);
t_ast				*create_node(void *data);

// PIPES
void				have_env(char **env, char **argv);
int					tramited(char *path, char **env);
