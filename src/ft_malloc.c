/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 05:10:51 by drestrep          #+#    #+#             */
/*   Updated: 2024/10/22 06:10:16 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
