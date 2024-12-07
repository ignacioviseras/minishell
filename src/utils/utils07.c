/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils07.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:11:16 by drestrep          #+#    #+#             */
/*   Updated: 2024/12/07 19:14:46 by drestrep         ###   ########.fr       */
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

int	skip_quoted_string(char	*str, int *counter)
{
	char	quote;

	if (str[*counter] == '"' || str[*counter] == '\'')
	{
		quote = str[(*counter)++];
		while (str[*counter] != quote)
			(*counter)++;
	}
	return (*counter);
}

char	*get_quoted_str(char *str, char quote)
{
	char	*quoted_str;
	int		i;

	i = 1;
	while (str[i] != quote)
		i++;
	i++;
	quoted_str = ft_malloc((i + 1) * sizeof(char));
	quoted_str[0] = str[0];
	i = 1;
	while (str[i] != quote)
	{
		quoted_str[i] = str[i];
		i++;
	}
	quoted_str[i++] = quote;
	quoted_str[i] = '\0';
	return (quoted_str);
}
