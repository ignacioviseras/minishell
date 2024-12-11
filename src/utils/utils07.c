/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils07.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:11:16 by drestrep          #+#    #+#             */
/*   Updated: 2024/12/11 17:05:02 by drestrep         ###   ########.fr       */
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
