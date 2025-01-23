/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils07.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:11:16 by drestrep          #+#    #+#             */
/*   Updated: 2025/01/23 16:22:58 by drestrep         ###   ########.fr       */
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

/* char	*get_unquoted_str(char *str)
{
	char	*unquoted_str;
	char	quote;
	int		i;

	i = 1;
	while (str[i + 1] != quote)
		i++;
	unquoted_str = ft_malloc((i + 1) * sizeof(char));
	unquoted_str[0] = str[1];
	i = 2;
	while (str[i] != quote)
	{
		unquoted_str[i - 1] = str[i];
		i++;
	}
	unquoted_str[i - 1] = '\0';
	return (unquoted_str);
} */

char	*get_unquoted_str(char *str)
{
	char	*unquoted_str;
	char	quote;
	int		i;
	int		nbr_of_quotes;

	i = 0;
	nbr_of_quotes = 0;
	if (findchar(str, '"') < 0 && findchar(str, '\'') < 0)
		return (str);
	printf("String: %s\n", str);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = str[i++];
			while (str[i] != quote)
				i++;
			nbr_of_quotes += 2;
		}
		i++;
	}
	unquoted_str = ft_malloc((i - nbr_of_quotes + 1) * sizeof(char));
	i = 0;
	nbr_of_quotes = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			i++;
			nbr_of_quotes++;
		}
		else
			i++;
		unquoted_str[i - nbr_of_quotes] = str[i];
	}
	unquoted_str[i - nbr_of_quotes] = '\0';
	return (unquoted_str);
}

char	*get_quoted_str(char *str, char quote)
{
	char	*quoted_str;
	int		i;

	i = 1;
	while (str[i] && str[i] != quote)
		i++;
	i++;
	quoted_str = ft_malloc((i + 1) * sizeof(char));
	quoted_str[0] = str[0];
	i = 1;
	while (str[i] && str[i] != quote)
	{
		quoted_str[i] = str[i];
		i++;
	}
	quoted_str[i++] = quote;
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
