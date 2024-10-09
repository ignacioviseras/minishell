/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:56:01 by drestrep          #+#    #+#             */
/*   Updated: 2024/10/09 20:26:27 by igvisera         ###   ########.fr       */
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
	TOKEN_PIPE,
	TOKEN_OUTPUT,
	TOKEN_INPUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_STRING,
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

//TODO:	This structure will be used to create the 
//TODO:	Abstract Syntax Tree (AST).
typedef struct s_tree
{
	void			*data;
	struct s_tree	*left;
	struct s_tree	*right;
}				t_tree;

/*
 * Structure representing a token
 * Each token holds a string value, a type, and a pointer to the next
 * token in the list.
 */
typedef struct s_token
{
	char			*value;
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


void				handle_input(char *line, char **envp);

t_token				*lexer(char *line);
void				automata_init(t_automata *automata);
int					transition_table(int i, int j);
int					get_symbol(char c);

// UTILS		
void				*ft_memset(void *b, int c, size_t len);
void				skip_spaces(const char *input, int *i);
void				ft_bzero(void *s, size_t n);
char				ft_lstlastchar(t_token *lst);
char				*ft_strdup(const char *s1);
size_t				ft_strlen(const char *str);
int					ft_strcmp(const char *str1, const char *str2);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
// static int			n_words(char const *s, char c);
char				**split_formated(char const *s, char c);
char				*ft_strjoin(char *s1, char *s2);
size_t				ft_strlcpy(char *dst, char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				**free_all(char **str);
char				*ft_str_toupper(char *str);


//BUILT_INS
void				built_switch(char **env, char *find);
char				*env_finder(char **env, char *find);
void				pwd(char **env);
void				cd();
void				env();


// TOKENIZER		
void				tokenize_strings(t_automata *automata, char *input, int *i);
void				tokenizer(t_automata *automata, char *input, int *i);
void				add_token(t_token **head, t_token *new_token);
t_token				*create_token(token_type type, char *value);

// PARSER		
void				parsing(t_token *tokens);

// PIPES
void	have_env(char **env, char **argv);
int		tramited(char *path, char **env);


