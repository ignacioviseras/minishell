/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:30:02 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/14 15:23:38 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// static void execute_pipe_left_child(t_ast *node, t_params *p, t_env *env, int in_fd)
// {
//     if (in_fd != -1)
//     {
//         if (dup2(in_fd, STDIN_FILENO) == -1)
//         {
//             perror("dup2");
//             exit(EXIT_FAILURE);
//         }
//         close(in_fd);
//     }
//     if (dup2(p->fd[1], STDOUT_FILENO) == -1)
//     {
//         perror("dup2");
//         exit(EXIT_FAILURE);
//     }
//     close(p->fd[0]);
//     close(p->fd[1]);
//     execute_ast(node->left, p, env, -1);
//     exit(EXIT_FAILURE);
// }

// static void execute_pipe_right_child(t_ast *node, t_params *p, t_env *env)
// {
//     if (dup2(p->fd[0], STDIN_FILENO) == -1)
//     {
//         perror("dup2");
//         exit(EXIT_FAILURE);
//     }
//     close(p->fd[0]);
//     close(p->fd[1]);
//     execute_ast(node->right, p, env, -1);
//     exit(EXIT_FAILURE);
// }

// void execute_pipe_ast(t_ast *node, t_params *p, t_env *env, int in_fd)
// {
//     pid_t pid_left, pid_right;

//     if (pipe(p->fd) == -1)
//     {
//         perror("pipe");
//         exit(EXIT_FAILURE);
//     }
//     pid_left = fork();
//     if (pid_left < 0)
//     {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }
//     if (pid_left == 0)
//         execute_pipe_left_child(node, p, env, in_fd);
//     pid_right = fork();
//     if (pid_right < 0)
//     {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }
//     if (pid_right == 0)
//         execute_pipe_right_child(node, p, env);
//     if (in_fd != -1)
//         close(in_fd);
//     close(p->fd[0]);
//     close(p->fd[1]);
//     waitpid(pid_left, &p->status, 0);
//     waitpid(pid_right, &p->status, 0);
// }

// void execute_simple_ast(t_ast *node, t_params *p, t_env *env, int in_fd)
// {
//     p->pid = fork();
//     if (p->pid < 0)
//     {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }
//     if (p->pid == 0)
//     {
//         if (in_fd != -1)
//         {
//             if (dup2(in_fd, STDIN_FILENO) == -1)
//             {
//                 perror("dup2");
//                 exit(EXIT_FAILURE);
//             }
//             close(in_fd);
//         }
//         before_execute(node, p, env);
//         exit(EXIT_FAILURE);
//     }
//     if (in_fd != -1)
//         close(in_fd);
//     waitpid(p->pid, &p->status, 0);
// }

// void execute_ast(t_ast *node, t_params *p, t_env *env, int in_fd)
// {
//     t_token *data;

//     if (node == NULL)
//         return;
//     data = (t_token *)node->data;
//     if (data->type == TOKEN_PIPE)
//         execute_pipe_ast(node, p, env, in_fd);
//     else
//         execute_simple_ast(node, p, env, in_fd);
// }

static void execute_pipe_left_child(t_ast *node, t_params *p, t_env *env, int in_fd) {
    if (in_fd != -1) {
        if (dup2(in_fd, STDIN_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(in_fd);
    }
    if (dup2(p->fd[1], STDOUT_FILENO) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(p->fd[0]);
    close(p->fd[1]);
    execute_ast(node->left, p, env, -1);
    exit(EXIT_FAILURE);
}

static void execute_pipe_right_child(t_ast *node, t_params *p, t_env *env) {
    if (dup2(p->fd[0], STDIN_FILENO) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(p->fd[0]);
    close(p->fd[1]);
    execute_ast(node->right, p, env, -1);
    exit(EXIT_FAILURE);
}

void execute_pipe_ast(t_ast *node, t_params *p, t_env *env, int in_fd) {
    pid_t pid_left, pid_right;

    if (pipe(p->fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid_left = fork();
    if (pid_left < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid_left == 0)
        execute_pipe_left_child(node, p, env, in_fd);
    pid_right = fork();
    if (pid_right < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid_right == 0)
        execute_pipe_right_child(node, p, env);
    if (in_fd != -1)
        close(in_fd);
    close(p->fd[0]);
    close(p->fd[1]);
    waitpid(pid_left, &p->status, 0);
    waitpid(pid_right, &p->status, 0);
}

void execute_simple_ast(t_ast *node, t_params *p, t_env *env, int in_fd) {
    p->pid = fork();
    if (p->pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (p->pid == 0) {
        if (in_fd != -1) {
            if (dup2(in_fd, STDIN_FILENO) == -1) {
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

void execute_ast(t_ast *node, t_params *p, t_env *env, int in_fd) {
    t_token *data;

    if (node == NULL)
        return;
    data = (t_token *)node->data;
    if (data->type == TOKEN_PIPE)
        execute_pipe_ast(node, p, env, in_fd);
    else
        execute_simple_ast(node, p, env, in_fd);
}

void	create_env(t_env *env, char **envp)
{
	while (envp && *envp)
	{
		env->key = ft_substr(*envp, 0, findchar(*envp, '='));
		env->value = ft_substr (*envp, findchar(*envp, '=') \
		+ 1, findchar(*envp, '\0'));
		env->hide = 0;
		if (*(envp + 1))
			env->next = ft_malloc(sizeof(t_env));
		else
			env->next = NULL;
		env = env->next;
		envp++;
	}
}

