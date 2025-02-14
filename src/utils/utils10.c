/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils10.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:54:18 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/14 17:30:31 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_quotes(const char *input, int *i, int *in_quotes,
		char *quote_type)
{
	if ((input[*i] == '\'' || input[*i] == '"'))
	{
		if (!(*in_quotes))
		{
			*in_quotes = 1;
			*quote_type = input[*i];
		}
		else if (input[*i] == *quote_type)
			*in_quotes = 0;
	}
	(*i)++;
}

void	handle_spaces(const char *input, int *i)
{
	while (input[*i] == ' ')
		(*i)++;
}

char	*extract_token(const char *input, int *i)
{
	int		start;
	int		in_quotes;
	char	quote_type;

	start = *i;
	in_quotes = 0;
	quote_type = 0;
	while (input[*i] && (in_quotes || input[*i] != ' '))
		handle_quotes(input, i, &in_quotes, &quote_type);
	if (in_quotes)
	{
		printf("Error: \" <- not closed\n");
		return (NULL);
	}
	return (ft_substr(input, start, *i - start));
}

char	**smart_split(const char *input)
{
	char	**result;
	int		i;
	int		j;

	result = ft_calloc(count_words_smart(input) + 1, sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		handle_spaces(input, &i);
		if (!input[i])
			break ;
		result[j] = extract_token(input, &i);
		if (!result[j])
		{
			free_matrix(result);
			return (NULL);
		}
		j++;
	}
	result[j] = NULL;
	return (result);
}

char	*ft_strcat(char *dest, const char *src)
{
	char	*ptr;

	ptr = dest + ft_strlen(dest);
	while (*src)
		*ptr++ = *src++;
	*ptr = '\0';
	return (dest);
}
