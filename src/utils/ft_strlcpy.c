/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:33:32 by igvisera          #+#    #+#             */
/*   Updated: 2024/10/23 11:31:42 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
