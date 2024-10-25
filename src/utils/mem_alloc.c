/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:36:11 by igvisera          #+#    #+#             */
/*   Updated: 2024/10/24 14:13:54 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	*ft_malloc(size_t size)
{
	void	*data;

	data = malloc(size);
	if (!data)
	{
		perror("Malloc failed");
		exit(1);
	}
	return (data);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;
	size_t	total_mem;

	if (nmemb == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	total_mem = nmemb * size;
	mem = malloc(total_mem);
	if (!mem)
		return (NULL);
	ft_bzero(mem, total_mem);
	return (mem);
}
