/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:30:02 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/01 21:06:46 by drestrep         ###   ########.fr       */
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

void	create_env(t_env *env, char **envp)
{
	while (envp && *envp)
	{
		env->key = ft_substr(*envp, 0, findchar(*envp, '='));
		env->value = ft_substr(*envp, findchar(*envp, '=') + 1, findchar(*envp,
					'\0'));
		env->hide = 0;
		if (*(envp + 1))
			env->next = ft_malloc(sizeof(t_env));
		else
			env->next = NULL;
		env = env->next;
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
