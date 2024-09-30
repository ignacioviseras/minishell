/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:56:01 by drestrep          #+#    #+#             */
/*   Updated: 2024/09/30 15:38:32 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#define USAGE_ERROR "Correct use: ./minishell\n"

typedef enum 
{
	EMPTY = 0,
	OPEN_DOUBLE_QUOTES,
	OPEN_SINGLE_QUOTES,
	PIPE_OPEN,
	INVALID_INPUT,
	SPACE_WITHOUT_WORDS,
	SPACE_BETWEEN_WORDS,
	NOT_OPERATORS
}			state;


typedef enum
{
	TOKEN_STRING,
    TOKEN_PIPE,
    TOKEN_IN,
	TOKEN_HEREDOC,
    TOKEN_OUT,
    TOKEN_APPEND,
	TOKEN_QUOTED_STRING,
    TOKEN_INVALID
}			token_type;

typedef enum
{
	INPUT_SPACE = 0,
	INPUT_PIPE,
	INPUT_DOUBLE_QUOTE,
	INPUT_SINGLE_QUOTE,
	INPUT_ELSE
} 			input;

typedef struct s_tree
{
	char			*data;
	struct s_tree	*left;
	struct s_tree	*right;
}				t_tree;

typedef struct s_token
{
	char			*value;
	token_type		type;
	struct s_token	*next;
}				t_token;


typedef struct s_automata
{
	t_token			*tokens;
	char			**alphabet;
	char			*token_start;
	char			buf[256];
	int				between_words;
	int				previous_state;
	int				state;
	int				i;
}				t_automata;

typedef struct s_input
{
	char			*line;
	char			**tokens;
}				t_input;

void	handle_input(t_input *input, char **envp);

// PARSING
t_token		*lexer(char *line);
void		automata_init(t_automata *automata);
int			transition_table(int i, int j);
int			get_input_type(char c);

// UTILS
char		*ft_strdup(const char *s1);
void		ft_bzero(void *s, size_t n);
int			ft_strcmp(const char *str1, const char *str2);
int			ft_strlen(char *str);

// TOKENIZER
void	tokenizer(t_automata *automata, char *input, int *i);
void	tokenize_words(t_automata *automata, char *input, int *i);
void	tokenize_words(t_automata *automata, char *input, int *i);
void	add_token(t_token **head, t_token *new_token);
t_token	*create_token(token_type type, char *value);
