/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:53:27 by drestrep          #+#    #+#             */
/*   Updated: 2024/11/19 16:09:42 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_quotes(char *str)
{
	int	nbr_of_quotes;
	int	quote;

	nbr_of_quotes = 0;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
		{
			quote = *str++;
			while (*str != quote)
				str++;
			nbr_of_quotes += 2;
		}
		str++;
	}
	return (nbr_of_quotes);
}

char	*unquote_str(char *str)
{
	char	*new_str;
	char	quote;
	int		i;
	int		j;

	new_str = ft_malloc((ft_strlen(str) - count_quotes(str) + 1) * \
	sizeof(char));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = str[i++];
			while (str[i] != quote)
				new_str[j++] = str[i++];
			i++;
		}
		if (str[i])
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*remove_quotes(char *str)
{
	if (!str)
		return (NULL);
	if (findchar(str, '"') == -1 && findchar(str, '\'') == -1)
		return (str);
	return (unquote_str(str));
}
