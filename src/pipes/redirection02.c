/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:58:28 by igvisera          #+#    #+#             */
/*   Updated: 2024/12/12 16:36:08 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

void redirect_append(t_token *data, t_ast *ast, t_params *p, t_env *env)
{
    if (ft_strcmp(data->cmd, ">>") != 0)
    {
        int original_stdout;
        int fd = open(data->cmd, O_WRONLY | O_CREAT | O_APPEND, 0644);
        original_stdout = dup(STDOUT_FILENO);
        if (fd < 0) {
            perror("open output");
            exit(EXIT_FAILURE);
        }
        if (dup2(fd, STDOUT_FILENO) < 0) {
            perror("dup2 output");
            close(fd);
            exit(EXIT_FAILURE);
        }
        close(fd);
        execute_node(ast->left, p, env);
        if (dup2(original_stdout, STDOUT_FILENO) < 0)
        {
            perror("restore stdin");
            exit(EXIT_FAILURE);
        }
        close(original_stdout);
    }
}

void init_redritect_append(t_ast *ast, t_params *p, t_env *env)
{
    if (ast->right->data != NULL)
    {
        t_token *token;

        token = (t_token *)(ast->right->data);
        redirect_append(token, ast, p, env);
    }
}