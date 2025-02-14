/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:43:00 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/14 17:43:15 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	create_pipe_processes(t_ast *node, t_params *p, t_env *env, int in_fd)
{
	p->pid_left = fork();
	if (p->pid_left < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (p->pid_left == 0)
		execute_pipe_left_child(node, p, env, in_fd);
	p->pid_right = fork();
	if (p->pid_right < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (p->pid_right == 0)
		execute_pipe_right_child(node, p, env);
}
