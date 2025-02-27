/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:32:52 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/26 18:19:12 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	before_execute(t_ast *node, t_params *p, t_env *env)
{
	t_token	*data;
	int		have_redirect;

	data = (t_token *)(node->data);
	have_redirect = have_redirection(data);
	if (have_redirect != -1)
		handle_redirection(node, env);
	execute_node(node, p, env);
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
	//int		pid;

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
