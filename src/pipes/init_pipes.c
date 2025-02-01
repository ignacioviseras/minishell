/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:30:02 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/01 21:09:23 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_ast(t_ast *node, t_params *p, t_env *env)
{
	t_token	*data;

	if (node == NULL)
		return ;
	data = (t_token *)(node->data);
	if (data->type == TOKEN_PIPE)
		handle_pipe(node, p, env);
	else
		before_execute(node, p, env);
}

void	pipe_error(int i, t_params *p)
{
	perror("pipe");
	while (i-- > 0)
	{
		close(p->fd[i * 2]);
		close(p->fd[i * 2 + 1]);
	}
	free(p->fd);
	exit(EXIT_FAILURE);
}

void	close_pipes(t_params *p)
{
	int	i;

	i = 0;
	while (i < 2 * p->total_cmds)
	{
		if (p->fd[i] != -1)
			close(p->fd[i]);
		i++;
	}
}

void	create_env(t_env **env, char **envp)
{
	t_env	*aux;
	t_env	*new_node;

	*env = NULL;
	aux = NULL;
	while (envp && *envp)
	{
		new_node = ft_malloc(sizeof(t_env));
		new_node->key = ft_substr(*envp, 0, findchar(*envp, '='));
		new_node->value = ft_substr(*envp, findchar(*envp, '=') + 1,
				findchar(*envp, '\0'));
		new_node->hide = 0;
		new_node->next = NULL;
		if (*env == NULL)
		{
			*env = new_node;
			aux = *env;
		}
		else
		{
			aux->next = new_node;
			aux = new_node;
		}
		envp++;
	}
}

void	init_pipes(t_ast *ast, t_params *p, t_env *env)
{
	int	i;
	int	resultpipe;

	p->fd = malloc(2 * p->total_cmds * sizeof(int));
	if (!p->fd)
		return ;
	ft_memset(p->fd, -1, 2 * p->total_cmds * sizeof(int));
	i = 0;
	while (i < p->total_cmds - 1)
	{
		resultpipe = pipe(p->fd + i * 2);
		if (resultpipe < 0)
			pipe_error(i, p);
		i++;
	}
	p->fd_index = 0;
	execute_ast(ast, p, env);
	close_pipes(p);
	free(p->fd);
	free_matrix(p->env);
}
