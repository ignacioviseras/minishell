/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:32:52 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/06 15:24:39 by drestrep         ###   ########.fr       */
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
	else
		execute_node(node, p, env);
}

void	wait_for_child(int pid, t_params *p)
{
	int	status;

	close(p->fd[p->fd_index + 1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
}

void	pipes_and_execute(t_ast *node, t_params *p, t_env *env, t_token *data)
{
	int	builtin;
	int	i;

	builtin = is_builtin(data->cmd);
	if (p->fd_index != 0)
		dup_read(p);
	if (p->fd_index < 2 * (p->total_cmds - 1))
		dup_write(p);
	i = 0;
	while (i < 2 * p->total_cmds)
	{
		// if (i != p->fd_index && i != p->fd_index + 1)
			close(p->fd[i]);
		i++;
	}
	if (data && data->type == TOKEN_PIPE)
		handle_pipe(node, p, env);
	else if (data && builtin == 0)
	{
		build_switch(env, node, data);
		exit(0);
	}
	else
		init_execute(data, p);
}

void	handle_processes(t_ast *node, t_params*p, t_env *env, t_token *data)
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

	data = (t_token *)(node->data);
	builtin = is_builtin(data->cmd);
	if (p->total_cmds == 1 && builtin == 0)
		build_switch(env, node, data);
	else
		handle_processes(node, p, env, data);
}
