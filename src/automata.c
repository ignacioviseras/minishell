/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:10:56 by drestrep          #+#    #+#             */
/*   Updated: 2024/09/11 18:33:05 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


int input_check(t_automata *automata)
{
	if (automata->state == 1 || automata->state == 2 ||
		automata->state == 3 || automata->state == 4)
	{
		if (automata->state == 1)
			printf("Invalid input, open double quotes\n");
		else if (automata->state == 2)
			printf("Invalid input, open single quotes\n");
		else if (automata->state == 3)
			printf("Invalid input, pipe open\n");
		else if (automata->state == 4)
			printf("Invalid input, open single quotes\n");
		return (0);
	}
	return (1);
}

// This table is required to get the final state of each char
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

int	get_input(char c)
{
	if (c == 32)
		return (INPUT_SPACE);
	if (c == '|')
		return (INPUT_PIPE);
	if (c == '"')
		return (INPUT_DOUBLE_QUOTE);
	if (c == '\'')
		return (INPUT_SINGLE_QUOTE);
	return (INPUT_ELSE);
}

void	automata_init(t_automata *automata)
{
	ft_bzero(automata, sizeof(t_automata));
	automata->previous_state = 0;
	automata->state = 0;
}

// Input's tokenization
int	lexical_analysis(t_input *input, char *line)
{
	t_automata	automata;
	int			c;
	int			i;

	i = -1;
	(void)input;
	automata_init(&automata);
	while (++i < ft_strlen(line))
	{
		c = get_input(line[i]);
		automata.state = transition_table(automata.previous_state, c);
		automata.previous_state = automata.state;
	}
	return (input_check(&automata));
}
