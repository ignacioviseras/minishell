/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:31:12 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/12 15:47:19 by igvisera         ###   ########.fr       */
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

void	handle_redirection(t_ast *node, t_params *p, t_env *env, int type)
{
	t_token	*data;

	data = (t_token *)(node->data);
	if (data == NULL)
		return ;
	if (type == INFILE)
		redirect_input(node);
	else if (type == WRITE)
		redirect_output(node);
	else if (type == APPEND)
		redirect_append(node);
	else if (type == HEREDOC)
		handle_heredoc(data, node, p, env);
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

void	create_env_null(t_env **env)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		*env = new_node("PWD", cwd, 0);
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
