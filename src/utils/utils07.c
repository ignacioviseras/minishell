/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils07.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:11:16 by drestrep          #+#    #+#             */
/*   Updated: 2025/02/20 17:33:47 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	skip_quoted_string(char	*str, int counter)
{
	char	quote;

	if (str[counter] == '"' || str[counter] == '\'')
	{
		quote = str[counter++];
		while (str[counter] != quote)
			counter++;
	}
	return (++counter);
}

char	*get_unquoted_str(char *str)
{
	char	*unquoted_str;
	char	quote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (findchar(str, '"') < 0 && findchar(str, '\'') < 0)
		return (ft_strdup(str));
	unquoted_str = ft_malloc((ft_strlen(str) - count_quotes(str) + 1) \
	* sizeof(char));
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				unquoted_str[j++] = str[i++];
			if (str[i] == quote)
				i++;
		}
		else
			unquoted_str[j++] = str[i++];
	}
	unquoted_str[j] = '\0';
	return (unquoted_str);
}

char	*get_str(char *old_str, char quote, int i, int odd_quotes)
{
	char	*new_str;

	new_str = ft_malloc((i + 1) * sizeof(char));
	if (odd_quotes == 0)
	{
		new_str[0] = old_str[0];
		i = 1;
		while (old_str[i] && old_str[i] != quote)
		{
			new_str[i] = old_str[i];
			i++;
		}
		new_str[i++] = quote;
	}
	else
	{
		i = 0;
		while (old_str[i + 1])
		{
			new_str[i] = old_str[i + 1];
			i++;
		}
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*get_quoted_str(char *str, char quote)
{
	char	*new_str;
	int		i;

	i = 1;
	while (str[i] && str[i] != quote)
		i++;
	if (!str[i])
		new_str = get_str(str, quote, i--, 1);
	else
		new_str = get_str(str, quote, i++, 0);
	return (new_str);
}

char	*ft_str(long aux, long size, long n1, int n)
{
	char	*str;

	str = (char *) malloc(size + 1 * sizeof(char));
	if (!str)
		return (NULL);
	str[size] = '\0';
	while (size > 0 && n >= 0)
	{
		aux = n1 % 10;
		n1 = n1 / 10;
		str[--size] = aux + '0';
	}
	while (size > 1 && n < 0)
	{
		str[0] = '-';
		aux = n1 % 10;
		n1 = n1 / 10;
		str[--size] = aux + '0';
	}
	return (str);
}
