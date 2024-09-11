/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:56:01 by drestrep          #+#    #+#             */
/*   Updated: 2024/09/11 18:25:13 by drestrep         ###   ########.fr       */
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
	INPUT_SPACE = 0,
	INPUT_PIPE,
	INPUT_DOUBLE_QUOTE,
	INPUT_SINGLE_QUOTE,
	INPUT_ELSE
} 			input;

typedef struct s_automata
{
	char	**alphabet;
	int		previous_state;
	int		state;
}				t_automata;

typedef struct s_input
{
	char	*line;
	char	**tokens;
}				t_input;

void	handle_input(t_input *input, char **envp);

// PARSING
int		lexical_analysis(t_input *input, char *line);
void	automata_init(t_automata *automata);
int		transition_table(int i, int j);
int		get_input(char c);


// UTILS
int		ft_strlen(char *str);
void	ft_bzero(void *s, size_t n);
int		ft_strcmp(const char *str1, const char *str2);
