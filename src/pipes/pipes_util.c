/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:43:00 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/20 17:20:44 by igvisera         ###   ########.fr       */
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

void	execute_simple_ast(t_ast *node, t_params *p, t_env *env, int in_fd)
{
	p->pid = fork();
	if (p->pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (p->pid == 0)
	{
		if (in_fd != -1)
		{
			if (dup2(in_fd, STDIN_FILENO) == -1)
			{
				perror("dup2");
				exit(EXIT_FAILURE);
			}
			close(in_fd);
		}
		before_execute(node, p, env);
		exit(EXIT_FAILURE);
	}
	if (in_fd != -1)
		close(in_fd);
	waitpid(p->pid, &p->status, 0);
}

void	execute_ast(t_ast *node, t_params *p, t_env *env, int in_fd)
{
	t_token	*data;

	if (node == NULL)
		return ;
	data = (t_token *)node->data;
	if (data->type == TOKEN_PIPE)
		execute_pipe_ast(node, p, env, in_fd);
	else if (is_builtin(data->cmd) == 0)
		before_execute(node, p, env);
	else
		execute_simple_ast(node, p, env, in_fd);
}
