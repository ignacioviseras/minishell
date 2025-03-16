/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:32:52 by igvisera          #+#    #+#             */
/*   Updated: 2025/03/10 17:35:56 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	fd_dup(int call)
{
	static int	stdin_copy;
	static int	stdout_copy;

	if (call == 0)
	{
		stdin_copy = dup(STDIN_FILENO);
		stdout_copy = dup(STDOUT_FILENO);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
	}
	else
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		dup2(stdin_copy, STDIN_FILENO);
		dup2(stdout_copy, STDOUT_FILENO);
	}
}

void	before_execute(t_ast *node, t_params *p, t_env *env)
{
	t_token	*data;
	int		have_redirect;
	int		error;

	error = 0;
	data = (t_token *)(node->data);
	have_redirect = have_redirection(data);
	if (have_redirect != -1)
	{
		if (is_builtin(data->cmd) == 0)
			fd_dup(0);
		error = handle_redirection(node);
	}
	if (error == 0)
		execute_node(node, p, env);
	if (have_redirect != -1 && is_builtin(data->cmd) == 0)
		fd_dup(1);
}

void	pipes_and_execute(t_ast *node, t_params *p, t_env *env, t_token *data)
{
	int	builtin;

	builtin = is_builtin(data->cmd);
	if (data->type == TOKEN_PIPE)
	{
		handle_pipe(node, p, env);
		return ;
	}
	else if (builtin == 0)
	{
		build_switch(env, node, data);
		exit(0);
	}
	else
		init_execute(data, p);
}

void	execute_node(t_ast *node, t_params *p, t_env *env)
{
	t_token	*data;
	int		builtin;

	data = (t_token *)(node->data);
	if (data->cmd != NULL)
	{
		builtin = is_builtin(data->cmd);
		if (p->total_cmds == 1 && builtin == 0)
			build_switch(env, node, data);
		else
			pipes_and_execute(node, p, env, data);
	}
}
