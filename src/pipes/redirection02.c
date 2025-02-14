/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:58:28 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/14 16:11:26 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// int	open_append_files(t_token *data)
// {
// 	int				fd;
// 	t_redirect_file	*outfile;
// 	t_list			*outfiles;

// 	fd = -1;
// 	outfiles = data->outfiles;
// 	while (outfiles)
// 	{
// 		outfile = (t_redirect_file *)outfiles->content;
// 		fd = open(outfile->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 		if (fd < 0)
// 		{
// 			perror("open append");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (outfiles->next)
// 			close(fd);
// 		outfiles = outfiles->next;
// 	}
// 	return (fd);
// }

// void	redirect_append(t_token *data, t_ast *ast, t_params *p, t_env *env)
// {
// 	int	fd;
// 	int	original_stdout;

// 	original_stdout = dup(STDOUT_FILENO);
// 	if (original_stdout < 0)
// 	{
// 		perror("dup original stdout");
// 		exit(EXIT_FAILURE);
// 	}
// 	fd = open_append_files(data);
// 	if (dup2(fd, STDOUT_FILENO) < 0)
// 	{
// 		perror("dup2 append");
// 		close(fd);
// 		exit(EXIT_FAILURE);
// 	}
// 	close(fd);
// 	execute_node(ast, p, env);
// 	restore_stdout(original_stdout);
// 	close(original_stdout);
// }

// void	init_redritect_append(t_ast *ast, t_params *p, t_env *env)
// {
// 	t_token	*token;

// 	token = (t_token *)(ast->data);
// 	redirect_append(token, ast, p, env);
// }
int open_append_files(t_token *data)
{
    int fd;
    t_redirect_file *outfile;
    t_list *outfiles;

    fd = -1;
    outfiles = data->outfiles;
    while (outfiles)
    {
        outfile = (t_redirect_file *)outfiles->content;
        fd = open(outfile->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd < 0)
        {
            perror("open append");
            exit(EXIT_FAILURE);
        }
        if (outfiles->next)
            close(fd);
        outfiles = outfiles->next;
    }
    return fd;
}

void redirect_append(t_token *data, t_ast *ast, t_params *p, t_env *env)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        int fd = open_append_files(data);
        if (dup2(fd, STDOUT_FILENO) < 0)
        {
            perror("dup2 append");
            close(fd);
            exit(EXIT_FAILURE);
        }
        close(fd);
        execute_node(ast, p, env);
        exit(EXIT_SUCCESS);
    }
    else
        waitpid(pid, &p->status, 0);
}

void init_redritect_append(t_ast *ast, t_params *p, t_env *env)
{
    t_token *token = (t_token *)(ast->data);
    redirect_append(token, ast, p, env);
}