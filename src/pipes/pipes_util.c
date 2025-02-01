/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:43:00 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/01 17:57:17 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	restore_stdin(int original_stdin)
{
	if (dup2(original_stdin, STDIN_FILENO) < 0)
	{
		perror("restore stdin");
		exit(EXIT_FAILURE);
	}
	close(original_stdin);
}

void	restore_stdout(int original_stdout)
{
	if (dup2(original_stdout, STDOUT_FILENO) < 0)
	{
		perror("restore stdout");
		exit(EXIT_FAILURE);
	}
	close(original_stdout);
}

char	*create_char(t_env *env)
{
	char	*str;
	char	*temp;

	if (!env || !env->key)
		return (NULL);
	str = ft_strdup(env->key);
	if (!str)
		return (NULL);
	if (env->value)
	{
		temp = ft_strjoin(str, "=");
		free(str);
		if (!temp)
			return (NULL);
		str = ft_strjoin(temp, env->value);
		free(temp);
		if (!str)
			return (NULL);
	}
	return (str);
}

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
