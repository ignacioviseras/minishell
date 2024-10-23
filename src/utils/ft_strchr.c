/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:33:01 by igvisera          #+#    #+#             */
/*   Updated: 2024/10/23 11:32:00 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	index;

	index = 0;
	while (s && s[index] != '\0')
	{
		if (s[index] == (unsigned char)c)
			return ((char *)s + index);
		index++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	return (NULL);
}
