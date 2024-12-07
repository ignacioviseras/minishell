/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:41:52 by drestrep          #+#    #+#             */
/*   Updated: 2024/12/07 15:01:31 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	copy_len(const char *s)
{
	int	i;

	i = 1;
	while (s[i] && s[i] != '$' && s[i] != ' ' && s[i] != '\'' && s[i] != '"')
		i++;
	return (i - 1);
}

char	*get_quoted_key(char *str, char *key, int *i)
{
	(*i)++;
	if (findchar(str + *i, '"') < findchar(str + *i, '$') && \
		findchar(str + *i, '$') >= 0)
		*i += findchar(str + *i, '"') + 1;
	else if (findchar(str + *i, '$') != -1 && \
		findchar(str + *i, '$') < findchar(str + *i, '"'))
	{
		key = ft_substr(str + *i, findchar(str + *i, '$') + 1, \
		copy_len(str + *i + findchar(str + *i, '$')));
		*i += findchar(str + *i, '$') + 1;
	}
	else
		*i += findchar(str + *i, '"') + 1;
	return (key);
}

char	*get_key(char *str, int *i)
{
	static int	quoted;
	char		*key;

	key = NULL;
	if (str[*i] == '\'' && quoted == 0)
		*i += findchar(str + *i + 1, '\'') + 2;
	else if (str[*i] == '"')
	{
		if (quoted == 0)
			quoted = 1;
		else if (quoted == 1)
			quoted = 0;
		key = get_quoted_key(str, key, i);
	}
	else if (str[*i] == '$')
	{
		key = ft_substr(str, *i + 1, copy_len(str + *i));
		*i += copy_len(str + *i) + 1;
	}
	else
		(*i)++;
	return (key);
}

char	**get_keys(char *str, int keys_nbr)
{
	char	**keys;
	char	*key;
	int		i;
	int		j;

	i = 0;
	j = 0;
	keys = ft_malloc((keys_nbr + 1) * sizeof(char *));
	while (str[i])
	{
		key = get_key(str, &i);
		if (key != NULL)
			keys[j++] = key;
	}
	keys[j] = NULL;
	return (keys);
}
