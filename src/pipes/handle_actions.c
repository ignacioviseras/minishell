/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:31:12 by igvisera          #+#    #+#             */
/*   Updated: 2025/03/10 17:38:42 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_pipe(t_ast *node, t_params *p, t_env *env)
{
	if (!node)
		return ;
	execute_ast(node->left, p, env, -1);
	execute_ast(node->right, p, env, -1);
}

int	handle_input_redirections(t_ast *node, t_token *data)
{
	t_list			*tmp;
	t_redirect_file	*redirection;
	int				error;

	error = 0;
	tmp = data->infiles;
	while (tmp)
	{
		redirection = (t_redirect_file *)tmp->content;
		if (redirection)
		{
			if (redirection->type == INFILE)
				error = redirect_input(node);
		}
		tmp = tmp->next;
	}
	return (error);
}

int	handle_output_redirections(t_ast *node, t_token *data)
{
	t_list			*tmp;
	t_redirect_file	*redirection;
	int				error;

	error = 0;
	tmp = data->outfiles;
	while (tmp)
	{
		redirection = (t_redirect_file *)tmp->content;
		if (redirection)
		{
			if (redirection->type == WRITE)
				error = redirect_output(node);
			else if (redirection->type == APPEND)
				error = redirect_append(node);
		}
		tmp = tmp->next;
	}
	return (error);
}

int	handle_redirection(t_ast *node)
{
	t_token	*data;
	int		error;

	data = (t_token *)(node->data);
	if (!data)
		return (1);
	error = handle_input_redirections(node, data);
	if (handle_output_redirections(node, data) < 0)
		error = -1;
	return (error);
}

int	is_builtin(char *cmd)
{
	char	*cmd_trim;
	char	*cmd_ar[8];
	int		i;

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
