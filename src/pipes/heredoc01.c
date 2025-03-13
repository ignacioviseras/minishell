/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:39:48 by igvisera          #+#    #+#             */
/*   Updated: 2025/03/13 16:15:57 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	process_single_heredoc(t_redirect_file *redir, t_env *env)
{
	char	*temp_filename;
	int		fd;
	pid_t	pid;

	fd = create_heredoc_file(&temp_filename);
	pid = fork();
	if (pid == 0)
		handle_heredoc_child(redir, env, fd);
	else if (pid > 0)
		handle_heredoc_parent(pid, fd, temp_filename, redir);
	else
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

static void	process_heredoc_list(t_list *list, t_env *env)
{
	t_redirect_file	*redir;

	while (list)
	{
		redir = (t_redirect_file *)list->content;
		if (redir && redir->type == HEREDOC)
			process_single_heredoc(redir, env);
		list = list->next;
	}
}

void	process_heredocs_in_ast(t_ast *node, t_env *env)
{
	t_token	*data;

	if (!node)
		return ;
	data = (t_token *)node->data;
	if (data->redir)
		process_heredoc_list(data->redir, env);
	process_heredocs_in_ast(node->left, env);
	process_heredocs_in_ast(node->right, env);
}
