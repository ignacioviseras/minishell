/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils07.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:11:16 by drestrep          #+#    #+#             */
/*   Updated: 2025/02/14 20:42:44 by drestrep         ###   ########.fr       */
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
	int		nbr_of_quotes;
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	if (findchar(str, '"') < 0 && findchar(str, '\'') < 0)
		return (ft_strdup(str));
	nbr_of_quotes = count_quotes(str);
	unquoted_str = ft_malloc((ft_strlen(str) - nbr_of_quotes + 1) \
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

char	*get_quoted_str(char *str, char quote)
{
	char	*quoted_str;
	int		odd_quotes;
	int		i;

	i = 1;
	odd_quotes = 0;
	while (str[i] && str[i] != quote)
		i++;
	if (!str[i])
	{
		i--;
		odd_quotes = 1;
	}
	else
		i++;
	quoted_str = ft_malloc((i + 1) * sizeof(char));
	if (odd_quotes == 0)
	{
		quoted_str[0] = str[0];
		i = 1;
		while (str[i] && str[i] != quote)
		{
			quoted_str[i] = str[i];
			i++;
		}
		quoted_str[i++] = quote;
	}
	else
	{
		i = 0;
		while (str[i + 1])
		{
			quoted_str[i] = str[i + 1];
			i++;
		}
	}
	quoted_str[i] = '\0';
	return (quoted_str);
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

char	*ft_itoa(int n)
{
	char	*str;
	long	size;
	long	aux;
	long	n1;

	size = 1;
	aux = (long)n;
	if (aux < 0)
	{
		aux *= -1;
		size++;
	}
	n1 = aux;
	while (aux >= 10)
	{
		aux = aux / 10;
		size++;
	}
	str = ft_str(aux, size, n1, n);
	return (str);
}
