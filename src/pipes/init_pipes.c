/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:30:02 by igvisera          #+#    #+#             */
/*   Updated: 2025/03/10 11:52:49 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	execute_pipe_left_child(t_ast *node, t_params *p, t_env *env,
		int in_fd)
{
	son_signal();
	if (in_fd != -1)
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(in_fd);
	}
	if (dup2(p->fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(p->fd[0]);
	close(p->fd[1]);
	execute_ast(node->left, p, env, -1);
	exit(EXIT_FAILURE);
}

static void	execute_pipe_right_child(t_ast *node, t_params *p, t_env *env)
{
	son_signal();
	if (dup2(p->fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(p->fd[0]);
	close(p->fd[1]);
	execute_ast(node->right, p, env, -1);
	exit(EXIT_FAILURE);
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

void	execute_pipe_ast(t_ast *node, t_params *p, t_env *env, int in_fd)
{
	if (pipe(p->fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	create_pipe_processes(node, p, env, in_fd);
	if (in_fd != -1)
		close(in_fd);
	close(p->fd[0]);
	close(p->fd[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(p->pid_left, &p->status, 0);
	waitpid(p->pid_right, &p->status, 0);
	if (WIFEXITED(p->status))
		g_exit_status = WEXITSTATUS(p->status);
	else if (WIFSIGNALED(p->status))
		g_exit_status = 128 + WTERMSIG(p->status);
}

void	before_create_env(t_env **env, char **envp)
{
	if (envp[0] == NULL)
		create_env_null(env);
	else
	{
		*env = ft_malloc(sizeof(t_env));
		create_env(*env, envp);
	}
}
