/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:10:56 by drestrep          #+#    #+#             */
/*   Updated: 2024/09/30 15:38:37 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	transition_table(int i, int j)
{
	const int	states[8][5] = {
		//   \s  |  "  '  ^
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

int	get_input_type(char c)
{
	if (c == ' ')
		return (INPUT_SPACE);
	if (c == '|')
		return (INPUT_PIPE);
	if (c == '"')
		return (INPUT_DOUBLE_QUOTE);
	if (c == '\'')
		return (INPUT_SINGLE_QUOTE);
	return (INPUT_ELSE);
}

void	skip_spaces(const char *input, int *i)
{
	while (input[*i] && input[*i] == ' ')
		(*i)++;
}

void	automata_init(t_automata *automata)
{
	automata->tokens = NULL;
	automata->state = 0;
	automata->previous_state = 0;
	memset(automata->buf, 0, sizeof(automata->buf));
}

// Automata-Driven Lexer:
// This lexer will use a Deterministic Finite Automaton (DFA) to 
// process the input string, handle state transitions, and produce tokens.
t_token	*lexer(char *input)
{
	t_automata	automata;
	int			i;

	i = 0;
	automata_init(&automata);
	while (input[i] != '\0')
	{
		skip_spaces(input, &i);
		if (input[i] == '\0')
			break ;
		tokenizer(&automata, input, &i);
		automata.state = \
		transition_table(automata.previous_state, get_input_type(input[i]));
		automata.previous_state = automata.state;
		if (automata.state == INVALID_INPUT)
		{
			printf("Invalid input detected\n");
			return (NULL);
		}
	}
	return (automata.tokens);
}
