/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils12.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:08:27 by drestrep          #+#    #+#             */
/*   Updated: 2025/02/20 18:34:47 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_size(char *str, int i)
{
	int	j;

	j = 0;
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
	return (j + 1);
}

char	*get_word(char *str, int i)
{
	char	*word;
	int		j;

	j = 0;
	word = ft_malloc(get_size(str, i) * sizeof(char));
	if (str[i] == '-')
	{
		while (str[i + j] && str[i + j] != '\'' && str[i + j] != ' ' \
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

/*
 * Returns the next word until the next space. ESTO YA NO APLICA
 * If the beginning of str is a space, it skips everything
 * until it finds something different.
 */
char	*get_next_word(char *cmd, char *str, int caller)
{
	int			i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i])
		return (NULL);
	if (str[i] == '\'' || str[i] == '"')
		return (get_quoted_str(str, str[i]));
	if (ft_strcmp(cmd, "echo") == 0 && str[i] == '-' && isalpha(str[i + 1]) \
		&& caller == 1 && str[i + 2] != ' ' && str[i + 2] != '\0')
		return (ft_strdup(str + i));
	return (get_word(str, i));
}
