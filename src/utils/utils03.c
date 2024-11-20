/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils03.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:05:12 by drestrep          #+#    #+#             */
/*   Updated: 2024/11/19 12:59:17 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	index;
	size_t	dst_lenght;
	size_t	src_lenght;

	index = 0;
	dst_lenght = ft_strlen(dst);
	src_lenght = ft_strlen(src);
	while (size <= dst_lenght)
		return (size + src_lenght);
	while (*dst)
		dst++;
	while (src[index] != '\0' && index < size - dst_lenght - 1)
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = '\0';
	return (dst_lenght + src_lenght);
}

size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	index;
	size_t	src_lenght;

	index = 0;
	src_lenght = ft_strlen(src);
	if (size == 0)
		return (src_lenght);
	while (src[index] != '\0' && index < size - 1)
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = '\0';
	return (src_lenght);
}

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	len;

	len = ft_strlen((char *)s);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, (char *)s, len + 1);
	return (ptr);
}

static size_t	ft_newstrlcpy(char *dst, char *src, size_t size)
{
	size_t	index;
	size_t	src_lenght;

	index = 0;
	src_lenght = ft_strlen(src);
	if (size == 0)
		return (src_lenght);
	while (src[index] != '\0' && index < size - 1)
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = ' ';
	dst[index + 1] = '\0';
	return (src_lenght + 1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*c1;
	size_t	len_max;

	if (!s1 || !s2)
		return (NULL);
	len_max = (ft_strlen(s1) + ft_strlen(s2)) + 2;
	if (!s1 || !s2)
		return (NULL);
	c1 = (char *)ft_calloc(len_max, sizeof(char));
	if (!c1)
		return (NULL);
	ft_newstrlcpy(c1, (char *)s1, ft_strlen((const char *)s1) + 1);
	ft_strlcat(c1, s2, len_max);
	return (c1);
}
