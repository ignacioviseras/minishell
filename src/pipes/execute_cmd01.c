/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:32:52 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/14 17:40:36 by igvisera         ###   ########.fr       */
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
		handle_redirection(node, p, env, have_redirect);
	execute_node(node, p, env);
}

void	wait_for_child(int pid, t_params *p)
{
	int	status;

	close(p->fd[0]);
	close(p->fd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
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

void	handle_processes(t_ast *node, t_params *p, t_env *env, t_token *data)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		pipes_and_execute(node, p, env, data);
	}
	else if (pid > 0)
	{
		signal(SIGINT, signals_handler_for_blockers);
		signal(SIGQUIT, signals_handler_for_blockers);
		wait_for_child(pid, p);
	}
	else
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

void	execute_node(t_ast *node, t_params *p, t_env *env)
{
	t_token	*data;
	int		builtin;
	int		pid;

	data = (t_token *)(node->data);
	if (data->cmd != NULL)
	{
		builtin = is_builtin(data->cmd);
		if (p->total_cmds == 1 && builtin == 0)
			build_switch(env, node, data);
		else
		{
			pid = fork();
			if (pid == 0)
				pipes_and_execute(node, p, env, data);
			else if (pid > 0)
				wait_for_child(pid, p);
			else
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
		}
	}
}
