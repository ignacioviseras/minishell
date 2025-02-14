/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:36:15 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/14 17:44:15 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_cmd(t_params *p)
{
	int	i;

	i = execve(p->cmd_path, p->cmd_exec, p->env);
	if (i < 0)
	{
		perror("execve");
		exit(126);
	}
}

int	tramited(char *path, t_params *p, t_token *t)
{
	char	**dir;
	char	*trim;

	dir = ft_split(path, ':');
	trim = trim_sp(t->full_cmd);
	if (ft_strcmp(trim, "./minishell") == 0)
		p->cmd_path = load_param(dir, t->full_cmd);
	else
		p->cmd_path = load_param(dir, t->cmd);
	p->cmd_exec = split_formated(remove_quotes(t->full_cmd), ' ');
	free(trim);
	free_matrix(dir);
	if (p->cmd_path != NULL)
		execute_cmd(p);
	else
	{
		free(p->cmd_path);
		free_matrix(p->cmd_exec);
		exit(127);
	}
	return (0);
}

void	init_execute(t_token *data, t_params *p)
{
	if (have_path(p->env) == 1)
		get_path(p->env, p, data);
	else if (ft_strchr(data->cmd, '/'))
		tramited("", p, data);
	else
		tramited("", p, data);
	return ;
}

int	search_priority(t_ast *node)
{
	int		res;
	t_token	*data;

	res = 0;
	if (node == NULL)
		return (0);
	data = (t_token *)(node->data);
	if (is_priority_command(data) == 1)
		res = 1;
	if (node->left)
		res = search_priority(node->left);
	if (node->right)
		res = search_priority(node->right);
	return (res);
}

int	is_priority_command(t_token *data)
{
	if (data->cmd && (ft_strcmp(data->cmd, "ls") == 0 || ft_strcmp(data->cmd,
				"pwd") == 0 || ft_strcmp(data->cmd, "env") == 0))
		return (1);
	return (0);
}
