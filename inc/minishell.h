/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:56:01 by drestrep          #+#    #+#             */
/*   Updated: 2024/10/07 14:25:39 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#define USAGE_ERROR "Correct use: ./minishell\n"

//* Each status represents one row in the DFA's transition table.
typedef enum 
{
	EMPTY,
	OPEN_DOUBLE_QUOTES,
	OPEN_SINGLE_QUOTES,
	PIPE_OPEN,
	LESS_OPEN,
	HEREDOC_OPEN,
	GREATER_OPEN,
	APPEND_OPEN,
	INVALID_INPUT,
	SPACE_WITHOUT_WORDS,
	SPACE_BETWEEN_WORDS,
	NOT_OPERATORS
}			status;

//* Types of tokens, used to create the AST in the parser.
typedef enum
{
	TOKEN_PIPE,
	TOKEN_STRING,
	TOKEN_INPUT,
	TOKEN_HEREDOC,
	TOKEN_OUTPUT,
	TOKEN_APPEND,
	TOKEN_QUOTED_STRING,
}			token_type;

/*
 *	Automaton's alphabet, each symbol represents one column in
 *	the DFA's transition table. 
 */
typedef enum
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
 *	 - Previous status: Well, I don't think I need to explain it tbh.
 */
typedef struct s_automata
{
	t_token			*tokens;
	char			buf[256];
	int				status;
	int				previous_status;
}				t_automata;


void				handle_input(char *line, char **envp);

t_token				*lexer(char *line);
void				automata_init(t_automata *automata);
int					transition_table(int i, int j);
int					get_symbol(char c);

// UTILS		
void				*ft_memset(void *b, int c, size_t len);
void				skip_spaces(const char *input, int *i);
void				ft_bzero(void *s, size_t n);
char				*ft_strdup(const char *s1);
int					ft_strlen(char *str);
int					ft_strcmp(const char *str1, const char *str2);

// TOKENIZER		
void				tokenize_strings(t_automata *automata, char *input, int *i);
void				tokenizer(t_automata *automata, char *input, int *i);
void				add_token(t_token **head, t_token *new_token);
t_token				*create_token(token_type type, char *value);

// PARSER		
void				parsing(t_token *tokens);

