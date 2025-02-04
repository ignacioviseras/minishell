/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils09.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:28:59 by drestrep          #+#    #+#             */
/*   Updated: 2025/02/04 15:44:49 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_alpha(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int	is_number(char c)
{
	return (c >= '0' && c <= '9');
}

int	is_alnum(char c)
{
	return (is_alpha(c) || is_number(c));
}

int	valid_char_filename(char c)
{
	if (c == ' ' || c == '\\' || c == '/' || c == ':' || c == '*' || \
		c == '?' || c == '<' || c == '>' || c == '|' || c == '&')
		return (0);
	return (1);
}

/*
 * Returns the next word until the next space.
 * If the beginning of str is a space, it skips everything
 * until it finds something different.
 */
char	*get_next_word(char *str)
{
	char	*word;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i])
		return (NULL);
	while (str[i + j] && str[i + j] != ' ')
		j++;
	word = ft_malloc((j + 1) * sizeof(char));
	j = 0;
	while (str[i + j] && str[i + j] != ' ')
	{
		word[j] = str[i + j];
		j++;
	}
	word[j] = '\0';
	return (word);
}


int count_words_smart(const char *input)
{
    int count = 0;
    int i = 0;
    int in_quotes = 0;
    char quote_type = 0;

    while (input[i])
    {
        while (input[i] == ' ')
            i++;
        if (!input[i])
            break;
        count++;
        while (input[i] && (in_quotes || input[i] != ' '))
        {
            if ((input[i] == '"' || input[i] == '\'') && (!in_quotes || input[i] == quote_type))
            {
                in_quotes = !in_quotes;
                quote_type = input[i];
            }
            i++;
        }
    }
    return count;
}

char	**smart_split(const char *input)
{
	char	**result;
	int		i, j, start;
	int		in_quotes;
	char	quote_type;

	result = ft_calloc(count_words_smart(input) + 1, sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		while (input[i] == ' ') // Saltar espacios al inicio
			i++;
		if (!input[i])
			break;
		start = i;
		in_quotes = 0;
		quote_type = 0;
		while (input[i] && (in_quotes || input[i] != ' '))
		{
			if ((input[i] == '\'' || input[i] == '"'))
			{
				if (!in_quotes) // Si no estaba en comillas, abrir
				{
					in_quotes = 1;
					quote_type = input[i];
				}
				else if (input[i] == quote_type) // Si es la misma comilla, cerrar
					in_quotes = 0;
			}
			i++;
		}
		if (in_quotes)
		{
			printf("Error: \" <- not closed\n");
			free_matrix(result);
			return (NULL);
		}
		result[j++] = ft_substr(input, start, i - start);
	}
	result[j] = NULL;
	return (result);
}
