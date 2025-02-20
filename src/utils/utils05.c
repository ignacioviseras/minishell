/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils05.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:11:56 by drestrep          #+#    #+#             */
/*   Updated: 2025/02/20 17:33:46 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_count_words(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

void	ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

// The same as ft_strlen but with char **
int	ft_strlen_v2(char **strs)
{
	int	i;
	int	j;
	int	total;

	j = 0;
	total = 0;
	if (!strs)
		return (0);
	while (strs[j])
	{
		i = 0;
		while (strs[j][i++] != '\0')
			total++;
		j++;
	}
	return (total);
}

int	is_valid(char *str)
{
	int	i;

	i = 1;
	if (!str || (!is_alpha(str[0]) && str[0] != '_'))
		return (1);
	while (str[i] != '\0')
	{
		if (!is_alnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
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
