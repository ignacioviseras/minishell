/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc03.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:40:37 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/14 18:16:25 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	create_heredoc_file(char **temp_filename)
{
	static int	heredoc_count;
	char		*count_str;
	char		*base_name;
	int			fd;

	base_name = ft_strdup(".heredoc.tmp.");
	heredoc_count++;
	count_str = ft_itoa(heredoc_count);
	if (!count_str)
		return (-1);
	*temp_filename = ft_strjoin(base_name, count_str);
	free(count_str);
	if (!*temp_filename)
		return (-1);
	fd = open(*temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open temp heredoc");
		return (-1);
	}
	free(base_name);
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
		redir->bool = 1;
		free(redir->value);
		redir->value = ft_strdup(temp_filename);
	}
	free(temp_filename);
}
