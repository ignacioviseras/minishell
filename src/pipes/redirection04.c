/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection04.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:39:48 by igvisera          #+#    #+#             */
/*   Updated: 2025/03/10 12:20:11 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	create_heredoc_file(char **temp_filename)
{
	int	fd;

	*temp_filename = ft_strdup(".heredoc.tmp");
	fd = open(*temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open temp heredoc");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	write_to_heredoc(int fd_file, char *buffer, t_env *env)
{
	char	*expanded;

	if (ft_strlen(buffer) > 0)
	{
		expanded = expand_variables_heredoc(buffer, env);
		free(buffer);
		buffer = expanded;
		if (write(fd_file, buffer, ft_strlen(buffer)) < 0)
		{
			perror("write heredoc");
			free(buffer);
			exit(EXIT_FAILURE);
		}
		if (write(fd_file, "\n", 1) < 0)
		{
			perror("write heredoc");
			free(buffer);
			exit(EXIT_FAILURE);
		}
	}
	free(buffer);
}

static void	process_single_heredoc(t_redirect_file *redir, t_env *env)
{
	char	*temp_filename;
	int		fd;
	pid_t	pid;
	int		status;

	fd = create_heredoc_file(&temp_filename);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, heredoc_signals_handler);
		signal(SIGQUIT, SIG_IGN);
		char *line;
		while ((line = readline("> ")) != NULL)
		{
			if (ft_strcmp(line, redir->value) == 0)
			{
				free(line);
				break;
			}
			write_to_heredoc(fd, line, env);
			//free(line);
		}
		close(fd);
		exit(0);
	}
	else if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT, signals_handler);
		close(fd);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
		if (g_exit_status == 130)
		{
			unlink(temp_filename);
			free(redir->value);
			redir->value = NULL;
		}
		else
		{
			redir->type = INFILE;
			free(redir->value);
			redir->value = ft_strdup(temp_filename);
		}
		free(temp_filename);
	}
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
	if (data->infiles)
		process_heredoc_list(data->infiles, env);
	process_heredocs_in_ast(node->left, env);
	process_heredocs_in_ast(node->right, env);
}
