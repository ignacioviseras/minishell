/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils09.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:28:59 by drestrep          #+#    #+#             */
/*   Updated: 2025/02/14 18:17:43 by drestrep         ###   ########.fr       */
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
 * Returns the next word until the next space. ESTO YA NO APLICA
 * If the beginning of str is a space, it skips everything
 * until it finds something different.
 */
char	*get_next_word(char *cmd, char *str, int caller)
{
	char		*word;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i])
		return (NULL);
	if (str[i] == '\'' || str[i] == '"')
		return (get_quoted_str(str, str[i]));
	if (ft_strcmp(cmd, "echo") == 0 && str[i] == '-' && isalpha(str[i + 1]) \
		&& caller == 1	&& str[i + 2] != ' ' && str[i + 2] != '\0')
		return(ft_strdup(str + i));
	if (str[i] == '-')
	{
		while (str[i + j] && str[i + j] != '\'' && str[i + j] != ' ' \
			&& str[i + j] != '"' && str[i + j] != '$')
			j++;
	}
	else
	{
		while (str[i + j] && str[i + j] != '\'' \
			&& str[i + j] != '"' && str[i + j] != '$')
			j++;
	}
	word = ft_malloc((j + 1) * sizeof(char));
	j = 0;
	if (str[i] == '-')
	{
		while (str[i + j] && str[i + j] != '\'' && str[i + j] != ' '\
		&& str[i + j] != '"' && str[i + j] != '$')
		{
			word[j] = str[i + j];
			j++;
		}
	}
	else
	{
		while (str[i + j] && str[i + j] != '\'' \
			&& str[i + j] != '"' && str[i + j] != '$')
		{
			word[j] = str[i + j];
			j++;
		}
	}
	word[j] = '\0';
	return (word);
}


