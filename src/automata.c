/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:10:56 by drestrep          #+#    #+#             */
/*   Updated: 2024/09/26 09:05:46 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


int input_check(int	state)
{
	if (state == 1 || state == 2 ||	state == 3 || state == 4)
	{
		if (state == 1)
			printf("Invalid input, open double quotes\n");
		else if (state == 2)
			printf("Invalid input, open single quotes\n");
		else if (state == 3)
			printf("Invalid input, pipe open\n");
		else if (state == 4)
			printf("Invalid input, open single quotes\n");
		return (0);
	}
	return (1);
}

t_token	*create_token(token_type type, char *value)
{
	t_token	*token;
	
	token = malloc(sizeof(t_token));
	token->type = type;
	token->value = strdup(value);
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *new_token)
{
	t_token *temp;

	if (*head == NULL)
		*head = new_token;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
}

char *extract_quoted_string(const char *input, int *i, char quote_type) {
    int start = ++(*i);
    while (input[*i] && input[*i] != quote_type)
        (*i)++;
    if (input[*i] == quote_type)
        (*i)++;
    return strndup(input + start, *i - start - 1); // Exclude closing quote
}
/* 
void	tokenizer(t_automata *automata, char *line, int i)
{
	char	token[3];
	int		start;

	// Handle quoted strings (double or single quotes)
    if (line[i] == '"' || line[i] == '\'')
	{
        char quote_type = line[i];
        char *quoted_string = extract_quoted_string(line, &i, quote_type);
        add_token(&automata->tokens, create_token(TOKEN_QUOTED_STRING, quoted_string));
        free(quoted_string);
    }
    // Handle operators
    if (line[i] == '|')
	{
        token[0] = '|';
        token[1] = '\0';
        add_token(&automata->tokens, create_token(TOKEN_PIPE, token));
        i++;
    }
	else
	{
        // Handle regular words (commands, arguments)
        start = i;
        while (line[i] && line[i] != ' ' && line[i] != '|' && line[i] != '>' && line[i] != '<')
            i++;
        strncpy(token, line + start, i - start);
        token[i - start] = '\0';
        add_token(&automata->tokens, create_token(TOKEN_STRING, token));
    }
} */
// Buffer characters into tokens based on the automata states
void	tokenizer(t_automata *automata, char *line, int i)
{
	char	symbol[3];

	if (automata->state >= 0 && automata->state <= 3)
	{
		if (automata->buffer_pos > 0)
		{
			automata->buffer[automata->buffer_pos] = '\0';
			add_token(&automata->tokens, \
			create_token(TOKEN_STRING, automata->buffer));
			automata->buffer_pos = 0;
		}
		symbol[1] = line[i];
		symbol[2] = '/0';
		add_token(&automata->tokens, create_token(get_input(line[i]), symbol));
	}
	else
		automata->buffer[automata->buffer_pos++] = line[i];
}

int	get_input(char c)
{
	if (c == ' ')
		return (0);
	if (c == '|')
		return (1);
	if (c == '"')
		return (2);
	if (c == '\'')
		return (3);
	return (4);
}

/* int	transition_table(int i, int j)
{
	const int	states[12][7] = {
//  \s  |  "  '  <  >  else
	{0, 8, 1, 2, 4, 6, 11},  // 0 Empty input
	{1, 1, 10, 1, 0, 0, 1},  // 1 Open double quotes
	{2, 2, 2, 10, 0, 0, 2},  // 2 Open single quotes
	{9, 8, 8, 8, 0, 0, 11},  // 3 Pipe open
	{4, 0, 0, 0, 5, 8, 11},  // 4 Input redirection open
	{5, 0, 0, 0, 8, 8, 0},   // 5 Heredoc open
	{0, 0, 0, 1, 8, 7, 0},   // 6 Output redirection open
	{0, 0, 0, 0, 8, 8, 0},   // 7 Append output redirection open
	{8, 8, 8, 8, 8, 8, 8},   // 8 Invalid input
	{9, 8, 1, 2, 0, 0, 11},  // 9 Spaces without words
	{10, 3, 1, 2, 0, 0, 11}, // 10 Spaces between words
	{10, 3, 1, 2, 0, 0, 11}, // 11 Not operators
	};

	return (states[i][j]);
} */

// DFA transition table: 
// This table is required to get the final state of each char
int	transition_table(int i, int j)
{
	const int	states[8][5] = {
//  \s  |  "  '  else
	{0, 3, 1, 2, 7}, // 0 Empty input
	{1, 1, 6, 1, 1}, // 1 Open double quotes
	{2, 2, 2, 6, 2}, // 2 Open single quotes
	{5, 4, 4, 4, 7}, // 3 Pipe open
	{4, 4, 4, 4, 4}, // 4 Invalid input
	{5, 4, 1, 2, 7}, // 5 Spaces without words
	{6, 3, 1, 2, 7}, // 6 Spaces between words
	{6, 3, 1, 2, 7}, // 7 Not operators
	};

	return (states[i][j]);
}

void	automata_init(t_automata *automata)
{
	ft_bzero(automata, sizeof(t_automata));
	automata->previous_state = 0;
	automata->state = 0;
	automata->between_words = 0;
	automata->tokens = NULL;
	automata->buffer_pos = 0;
}

// Automata-Driven Lexer:
// This lexer will use a Deterministic Finite Automaton (DFA) to 
// process the input string, handle state transitions, and produce tokens.
t_token	*lexer(char *line)
{
	t_automata	automata;
	int			i;

	i = 0;
	while (line[i] && line[i] == ' ')
        i++;
	automata_init(&automata);
	while (++i < ft_strlen(line))
	{
		automata.state = transition_table \
		(automata.previous_state, get_input(line[i]));
		tokenizer(&automata, line, i);
		automata.tokens = NULL;
		return (automata.tokens);
		automata.previous_state = automata.state;
		i++;
	}
	input_check(automata.state);
	return (automata.tokens);
}
