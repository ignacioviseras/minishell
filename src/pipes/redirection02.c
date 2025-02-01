/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:58:28 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/01 16:03:07 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

void redirect_append(t_token *data, t_ast *ast, t_params *p, t_env *env)
{
    int fd;
    int original_stdout;
    t_redirect_file *outfile;
    t_list *outfiles;

    fd = -1;
    original_stdout = dup(STDOUT_FILENO);
    if (original_stdout < 0)
    {
        perror("dup original stdout");
        exit(EXIT_FAILURE);
    }
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
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        perror("dup2 append");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
    execute_node(ast, p, env);
    if (dup2(original_stdout, STDOUT_FILENO) < 0)
    {
        perror("restore stdout");
        exit(EXIT_FAILURE);
    }
    close(original_stdout);
}

void init_redritect_append(t_ast *ast, t_params *p, t_env *env)
{
    t_token *token;

    token = (t_token *)(ast->data);
    redirect_append(token, ast, p, env);
}
