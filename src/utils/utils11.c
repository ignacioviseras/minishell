/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils11.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:21:43 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/04 18:22:13 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


void	handle_word_quotes(const char *input, int *i, int *in_quotes, char *quote_type)
{
	if ((input[*i] == '"' || input[*i] == '\'') && (!(*in_quotes) || input[*i] == *quote_type))
	{
		*in_quotes = !(*in_quotes);
		*quote_type = input[*i];
	}
	(*i)++;
}

void	skip_spaces(const char *input, int *i)
{
	while (input[*i] == ' ')
		(*i)++;
}

int	count_words_smart(const char *input)
{
	int		count;
	int		i;
	int		in_quotes;
	char	quote_type;

	count = 0;
	i = 0;
	in_quotes = 0;
	quote_type = 0;
	while (input[i])
	{
		skip_spaces(input, &i);
		if (!input[i])
			break;
		count++;
		while (input[i] && (in_quotes || input[i] != ' '))
			handle_word_quotes(input, &i, &in_quotes, &quote_type);
	}
	return (count);
}
