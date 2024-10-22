/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:10:56 by drestrep          #+#    #+#             */
/*   Updated: 2024/10/22 06:10:55 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
 * A transition table that returns the next state based on the current state (i)
 * and input (j).
 *
 *		- Each row represents the status of the DFA.
 *		- Each column represents the input type.
 *		- Each cell contains the next status to which the DFA transitions.
 */
int	transition_table(int i, int j)
{
	const int	status[][8] = {
		//   \S,  |,  <,  >,  ",  ',  ^
	{0, 8, 4, 6, 1, 2, 11},		// 0  Empty input
	{1, 1, 1, 1, 10, 1, 1},		// 1  Open double quotes
	{2, 2, 2, 2, 2, 10, 2},		// 2  Open single quotes
	{9, 8, 8, 8, 1, 2, 11},		// 3  Pipe open
	{9, 8, 5, 8, 1, 2, 11},		// 4  Less open
	{9, 8, 8, 8, 1, 2, 11},		// 5  Heredoc open
	{9, 8, 8, 7, 1, 2, 11},		// 6  Greater open
	{9, 8, 8, 8, 1, 2, 11},		// 7  Append open
	{8, 8, 8, 8, 8, 8, 8},		// 8  Invalid input
	{9, 1, 1, 1, 1, 2, 11},		// 9  Spaces without words
	{10, 3, 4, 6, 1, 2, 11},	// 10 Spaces between words
	{10, 3, 4, 6, 1, 2, 11},	// 11 Not operators
	};

	return (status[i][j]);
}

/*
 *	Returns the value assigned to each character of the input string
 *	to use it on the transition table.
*/
int	get_symbol(char c)
{
	if (c == ' ')
		return (INPUT_SPACE);
	if (c == '|')
		return (INPUT_PIPE);
	if (c == '<')
		return (INPUT_LESS);
	if (c == '>')
		return (INPUT_GREATER);
	if (c == '"')
		return (INPUT_DOUBLE_QUOTE);
	if (c == '\'')
		return (INPUT_SINGLE_QUOTE);
	return (INPUT_ELSE);
}

/* 
 *	Checks whether the input is valid or not, based on the status returned
 *	by the DFA transition table.
 */
int	input_checker(t_automata *automata, char *input)
{
	int		i;

	i = 0;
	while (input[i] != '\0')
	{
		automata->status = \
		transition_table(automata->status, get_symbol(input[i]));
		i++;
		if ((input[i] == '\0' && automata->status <= 9) || \
			(get_symbol(ft_lstlastchar(automata->tokens)) > 0 && \
			get_symbol(ft_lstlastchar(automata->tokens)) < 4))
		{
			printf("syntax error\n");
			return (0);
		}
	}
	return (1);
}

/*
 * Initialize each value of the referenced automata.
 */
void	automata_init(t_automata *automata)
{
	automata->tokens = NULL;
	automata->status = 0;
	ft_memset(automata->buf, 0, sizeof(automata->buf));
}

/*
 *	Automata-Driven Lexer
 *
 *	This lexer will use a Deterministic Finite Automaton (DFA) to 
 *	process the input string, handle state transitions, and produce tokens.
 *
 *	Returns an array of tokens to create a binary tree.
 */
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
	}
	if (!input_checker(&automata, input))
		return (NULL);
	return (automata.tokens);
}
