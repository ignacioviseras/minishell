/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection06.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:40:37 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/10 13:49:59 by drestrep         ###   ########.fr       */
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

void	handle_heredoc_child(t_redirect_file *redir, t_env *env, int fd)
{
	char	*line;

	signal(SIGINT, heredoc_signals_handler);
	signal(SIGQUIT, SIG_IGN);
	line = readline("> ");
	while (line != NULL)
	{
		if (ft_strcmp(line, redir->value) == 0)
		{
			free(line);
			break ;
		}
		write_to_heredoc(fd, line, env);
		line = readline("> ");
	}
	close(fd);
	exit(0);
}

void	handle_heredoc_parent(pid_t pid, int fd, \
	char *temp_filename, t_redirect_file *redir)
{
	int	status;

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
