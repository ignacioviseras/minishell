/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils09.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:28:59 by drestrep          #+#    #+#             */
/*   Updated: 2025/02/04 17:54:40 by igvisera         ###   ########.fr       */
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
