/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:31:12 by igvisera          #+#    #+#             */
/*   Updated: 2024/12/17 18:10:18 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

void	handle_pipe(t_ast *node, t_params *p, t_env *env)
{
	if (!node)
        return;
	execute_ast(node->left, p, env);//procesar el nodo recursivamente lado izq
	p->fd_index += 2;//mover index para extemos de los dups
	execute_ast(node->right, p, env);//procesar el nodo recursivamente lado derch
}

void handle_redirection(t_ast *node, t_params *p, t_env *env)
{
    t_token *data;

    data = (t_token *)(node->data);
    if (data == NULL)
        return;
    //if (ft_strcmp(data->cmd, "<") == 0)
    // else if (ft_strcmp(data->cmd, ">") == 0)
    //else if (ft_strcmp(data->cmd, ">>") == 0)
    //else if (ft_strcmp(data->cmd, "<<") == 0)
    if (data->type == TOKEN_INPUT)
        init_redirct_in(node, p, env);
    else if (data->type == TOKEN_OUTPUT)
        init_redirct_out(node, p, env);
    else if (data->type == TOKEN_APPEND)
        init_redritect_append(node, p, env);
    else if (data->type == TOKEN_HEREDOC)
    {
        handle_heredoc(data, node, p);
        execute_node(node->right, p, env);
    }
    // if (node->left)
    //     handle_redirection(node->left, p, env);
    // if (node->right)
    //     handle_redirection(node->right, p, env);
}


int is_builtin(char *cmd)
{
	char *cmd_trim;
	char *cmd_ar[8];
	int i;

	if (!cmd)
		return (1);
	i = 0;
    cmd_trim = trim_sp(cmd);
	cmd_ar[0] = "pwd";
    cmd_ar[1] = "env";
    cmd_ar[2] = "cd";
    cmd_ar[3] = "echo";
    cmd_ar[4] = "export";
    cmd_ar[5] = "unset";
    cmd_ar[6] = "clear";
    cmd_ar[7] = "exit";
	while (i < 8)
	{
		if (ft_strcmp(cmd_trim, cmd_ar[i]) == 0)
			return (free(cmd_trim), 0);
		i++;
	}
	return (free(cmd_trim), 1);
}
