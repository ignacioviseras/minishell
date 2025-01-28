/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:12:20 by igvisera          #+#    #+#             */
/*   Updated: 2025/01/28 17:58:46 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	**free_matrix(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	return (free(str), NULL);
}

void	free_variable(t_env *node)
{
	free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

/* void	free_env_matrix(char **env_matrix)
{
	int	i;

	i = 0;
	while (env_matrix[i])
	{
		free(env_matrix[i]);
		i++;
	}
	free(env_matrix);
} */
