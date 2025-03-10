/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:06:24 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/10 12:06:44 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_env_nodes(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	**init_env(t_env *env)
{
	char	**env_matrix;
	int		env_count;
	int		x;

	env_count = count_env_nodes(env);
	env_matrix = ft_malloc((env_count + 1) * sizeof(char *));
	if (!env_matrix)
		return (NULL);
	x = 0;
	while (env)
	{
		env_matrix[x] = create_char(env);
		if (!env_matrix[x])
		{
			while (x-- > 0)
				free(env_matrix[x]);
			free(env_matrix);
			return (NULL);
		}
		x++;
		env = env->next;
	}
	env_matrix[x] = NULL;
	return (env_matrix);
}
