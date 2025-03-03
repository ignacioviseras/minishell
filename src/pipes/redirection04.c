/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection04.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:39:48 by igvisera          #+#    #+#             */
/*   Updated: 2025/03/03 15:24:53 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_heredoc(void)
{
	int	fd;

	fd = open(".heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open heredoc");
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

int	read_heredoc(void)
{
	int	fd_file;

	fd_file = open(".heredoc.tmp", O_RDONLY);
	if (fd_file < 0)
	{
		perror("open heredoc tmp");
		exit(EXIT_FAILURE);
	}
	return (fd_file);
}

//TODO: SIGNALS EN EL HEREDOC
int	process_heredoc(t_token *data, t_env *env)
{
	int				fd_file;
	char			*buffer;
	t_list			*heredoc;
	t_redirect_file	*heredocs;

	heredoc = data->infiles;
	heredocs = (t_redirect_file *)heredoc->content;
	fd_file = open_heredoc();
	//signal(SIGINT, heredoc_signals_handler);
	//signal(SIGQUIT, heredoc_signals_handler);
	while (1)
	{
		buffer = readline("> ");
		if (buffer == NULL || ft_strcmp(buffer, heredocs->value) == 0)
		{
			free(buffer);
			break ;
		}
		write_to_heredoc(fd_file, buffer, env);
	}
	close(fd_file);
	fd_file = read_heredoc();
	return (fd_file);
}

void	handle_heredoc(t_token *data, t_env *env)
{
	int	hd_fd;

	hd_fd = process_heredoc(data, env);
	if (hd_fd == -1)
		return ;
	if (dup2(hd_fd, STDIN_FILENO) == -1)
	{
		perror("dup2 heredoc");
		close(hd_fd);
		exit(EXIT_FAILURE);
	}
	close(hd_fd);
	unlink(".heredoc.tmp");
}
