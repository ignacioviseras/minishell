/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils05.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:11:56 by drestrep          #+#    #+#             */
/*   Updated: 2024/12/11 19:52:39 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

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
