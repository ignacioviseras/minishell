/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:53:37 by drestrep          #+#    #+#             */
/*   Updated: 2024/09/11 13:48:08 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int ft_strlen(char *str)
{
    int i;

	i = 0;
    while (*str != '\0')
    {
        str++;
        i++;
    }
    return i;
}


void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*k;

	i = 0;
	k = (char *) s;
	while (i < n)
		k[i++] = 0;
}

int	ft_strcmp(const char *str1, const char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return *(unsigned char *)str1 - *(unsigned char *)str2;
}
