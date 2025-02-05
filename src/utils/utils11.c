/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils11.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:21:43 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/05 17:57:24 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_word_quotes(const char *input, int *i, int *in_quotes,
		char *quote_type)
{
	if ((input[*i] == '"' || input[*i] == '\'') && (!(*in_quotes)
			|| input[*i] == *quote_type))
	{
		*in_quotes = !(*in_quotes);
		*quote_type = input[*i];
	}
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
		skip_spaces((char *)input, &i);
		if (!input[i])
			break ;
		count++;
		while (input[i] && (in_quotes || input[i] != ' '))
			handle_word_quotes(input, &i, &in_quotes, &quote_type);
	}
	return (count);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	sgn;
	int	i;

	res = 0;
	sgn = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if ((str[i] == '+') || (str[i] == '-'))
	{
		if (str[i] == '-')
			sgn *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (sgn * res);
}
