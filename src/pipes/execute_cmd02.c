/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:36:15 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/01 17:57:42 by igvisera         ###   ########.fr       */
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
		g_exit_status = 126;
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

void	dup_read(t_params *p)
{
	int	result;

	result = dup2(p->fd[p->fd_index - 2], 0);
	if (result < 0)
	{
		perror("dup2 input");
		exit(EXIT_FAILURE);
	}
}

void	dup_write(t_params *p)
{
	int	result;

	result = dup2(p->fd[p->fd_index + 1], 1);
	if (result < 0)
	{
		perror("dup2 output");
		exit(EXIT_FAILURE);
	}
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
