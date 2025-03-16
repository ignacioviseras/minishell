/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:43:00 by igvisera          #+#    #+#             */
/*   Updated: 2025/03/10 12:15:27 by drestrep         ###   ########.fr       */
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

void	handle_fork_error(void)
{
	perror("fork");
	exit(EXIT_FAILURE);
}

void	handle_child_process(t_ast *node, t_params *p, t_env *env, int in_fd)
{
	signal(SIGQUIT, SIG_DFL);
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

void	execute_simple_ast(t_ast *node, t_params *p, t_env *env, int in_fd)
{
	p->pid = fork();
	if (p->pid < 0)
		handle_fork_error();
	if (p->pid == 0)
		handle_child_process(node, p, env, in_fd);
	if (in_fd != -1)
		close(in_fd);
	signal(SIGINT, signals_handler_for_blockers);
	signal(SIGQUIT, signals_handler_for_blockers);
	waitpid(p->pid, &p->status, 0);
	if (WIFEXITED(p->status))
		g_exit_status = WEXITSTATUS(p->status);
	else if (WIFSIGNALED(p->status))
		g_exit_status = 128 + WTERMSIG(p->status);
	// if (p->pid_right == 0)
	// 	exit(g_exit_status);
}

void	execute_ast(t_ast *node, t_params *p, t_env *env, int in_fd)
{
	t_token	*data;

	if (node == NULL || g_exit_status == 130)
		return ;
	data = (t_token *)node->data;
	if (data->type == TOKEN_PIPE)
		execute_pipe_ast(node, p, env, in_fd);
	else if (is_builtin(data->cmd) == 0)
		before_execute(node, p, env);
	else
		execute_simple_ast(node, p, env, in_fd);
}
