/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:03:53 by igvisera          #+#    #+#             */
/*   Updated: 2025/01/28 19:19:08 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

// void redirect_input(t_token *data, t_ast *ast, t_params *p, t_env *env)
// {
//     int fd;
//     int original_stdin;

//     dprintf(2, "data->cmd '%s'\n", data->cmd);
//     fd = open("./qwe", O_RDONLY);
//     // fd = open(data->cmd, O_RDONLY);
//     original_stdin = dup(STDIN_FILENO);
//     if (fd < 0)
//     {
//         perror("open input");
//         exit(EXIT_FAILURE);
//     }
//     if (dup2(fd, STDIN_FILENO) < 0)
//     {
//         perror("dup2 input");
//         exit(EXIT_FAILURE);
//     }
//     close(fd);
//     execute_node(ast, p, env);
//     if (dup2(original_stdin, STDIN_FILENO) < 0)
//     {
//         perror("restore stdin");
//         exit(EXIT_FAILURE);
//     }
//     close(original_stdin);
// }
void redirect_input(t_token *data, t_ast *ast, t_params *p, t_env *env)
{
    int fd = -1;
    int original_stdin;
    t_redirect_file *infile;
    t_list *infiles;

    original_stdin = dup(STDIN_FILENO);
    if (original_stdin < 0)
    {
        perror("dup original stdin");
        exit(EXIT_FAILURE);
    }
    infiles = data->infiles;
    while (infiles)
    {
        infile = (t_redirect_file *)infiles->content;
        dprintf(2, "infile->value '%s'\n", infile->value);

        // Abrir archivo en modo lectura
        fd = open(infile->value, O_RDONLY);
        if (fd < 0)
        {
            perror("open input");
            exit(EXIT_FAILURE);
        }
        if (infiles->next)
            close(fd);
        infiles = infiles->next;
    }
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        perror("dup2 input");
        exit(EXIT_FAILURE);
    }
    close(fd);
    execute_node(ast, p, env);
    if (dup2(original_stdin, STDIN_FILENO) < 0)
    {
        perror("restore stdin");
        exit(EXIT_FAILURE);
    }
    close(original_stdin);
}

void init_redirct_in(t_ast *ast, t_params *p, t_env *env)
{
    t_token *token;

    token = (t_token *)(ast->data);
    redirect_input(token, ast, p, env);
}

// void redirect_output(t_token *data, t_ast *ast, t_params *p, t_env *env)
// {
//     dprintf(2, "data->cmd '%s'\n", data->cmd);

//     int original_stdout;
// 	t_redirect_file	*outfile;

//     outfile = (t_redirect_file *)data->outfiles->content;
//     dprintf(2, "outfile->value '%s'\n", outfile->value);
//     int fd = open(outfile->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     // int fd = open(data->args, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     original_stdout = dup(STDOUT_FILENO);
//     if (fd < 0) {
//         perror("open output");
//         exit(EXIT_FAILURE);
//     }
//     if (dup2(fd, STDOUT_FILENO) < 0) {
//         perror("dup2 output");
//         exit(EXIT_FAILURE);
//     }
//     close(fd);
//     execute_node(ast, p, env);
//     if (dup2(original_stdout, STDOUT_FILENO) < 0)
//     {
//         perror("restore stdin");
//         exit(EXIT_FAILURE);
//     }
//     close(original_stdout);
// }

void redirect_output(t_token *data, t_ast *ast, t_params *p, t_env *env)
{
    int original_stdout;
    int fd;
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
        fd = open(outfile->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
        {
            perror("open output");
            exit(EXIT_FAILURE);
        }
        if (outfiles->next)
            close(fd);
        outfiles = outfiles->next;
    }
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        perror("dup2 output");
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


void init_redirct_out(t_ast *ast, t_params *p, t_env *env)
{
    t_token *token;
    
    token = (t_token *)(ast->data);
    redirect_output(token, ast, p, env);
}
