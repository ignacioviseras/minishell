/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:03:53 by igvisera          #+#    #+#             */
/*   Updated: 2024/12/12 15:58:21 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

void redirect_input(t_token *data, t_ast *ast, t_params *p, t_env *env)
{
    if (ft_strcmp(data->cmd, "<") != 0)
    {
        int fd;
        int original_stdin;

        fd = open(data->cmd, O_RDONLY);
        original_stdin = dup(STDIN_FILENO);
        if (fd < 0)
        {
            perror("open input");
            exit(EXIT_FAILURE);
        }
        if (dup2(fd, STDIN_FILENO) < 0)
        {
            perror("dup2 input");
            exit(EXIT_FAILURE);
        }
        close(fd);
        execute_node(ast->left, p, env);
        if (dup2(original_stdin, STDIN_FILENO) < 0)
        {
            perror("restore stdin");
            exit(EXIT_FAILURE);
        }
        close(original_stdin);
    }
}

void init_redirct_in(t_ast *ast, t_params *p, t_env *env)
{
    if (ast->right->data != NULL)
    {
        t_token *token;

        token = (t_token *)(ast->right->data);
        redirect_input(token, ast, p, env);
    }
}

void redirect_output(t_token *data, t_ast *ast, t_params *p, t_env *env)
{
    dprintf(2, "BBBBBBBBBBBB '%s'\n", data->cmd);

    if (ft_strcmp(data->cmd, ">") == 0)
    {
        dprintf(2, "AACCCEEEDEEE\n");
        int original_stdout;
        int fd = open(data->args, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        original_stdout = dup(STDOUT_FILENO);
        if (fd < 0) {
            perror("open output");
            exit(EXIT_FAILURE);
        }
        if (dup2(fd, STDOUT_FILENO) < 0) {
            perror("dup2 output");
            exit(EXIT_FAILURE);
        }
        close(fd);
        execute_node(ast->right, p, env);
        if (dup2(original_stdout, STDOUT_FILENO) < 0)
        {
            perror("restore stdin");
            exit(EXIT_FAILURE);
        }
        close(original_stdout);
    }
}

void init_redirct_out(t_ast *ast, t_params *p, t_env *env)
{
    // if (ast->right->data != NULL)
    // {
        t_token *token;
        dprintf(2, "QWEQWEQWE\n");

    //     token = (t_token *)(ast->right->data);
        token = (t_token *)(ast->right->data);
        redirect_output(token, ast, p, env);

    // }
}
