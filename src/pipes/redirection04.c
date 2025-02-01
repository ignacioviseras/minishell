/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection04.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:39:48 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/01 17:56:22 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_heredoc(void)
{
	int	fd_file;

	fd_file = open(".heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_file < 0)
	{
		perror("open heredoc");
		exit(EXIT_FAILURE);
	}
	return (fd_file);
}

void	write_to_heredoc(int fd_file, char *buffer)
{
	ssize_t	content;
	ssize_t	cnt;

	content = write(fd_file, buffer, ft_strlen(buffer));
	if (content < 0)
	{
		perror("write to heredoc file");
		free(buffer);
		exit(EXIT_FAILURE);
	}
	cnt = write(fd_file, "\n", 1);
	if (cnt < 0)
	{
		perror("write to heredoc file");
		free(buffer);
		exit(EXIT_FAILURE);
	}
}

void	write_heredoc(int fd_file, char *delimiter)
{
	char	*buffer;

	buffer = NULL;
	while (1)
	{
		buffer = readline("> ");
		if (buffer == NULL || ft_strcmp(buffer, delimiter) == 0)
		{
			free(buffer);
			break ;
		}
		if (ft_strlen(buffer) > 0)
			write_to_heredoc(fd_file, buffer);
		free(buffer);
	}
}

void	set_heredoc_input(int fd_file)
{
	if (fd_file < 0)
	{
		perror("open heredoc file");
		exit(EXIT_FAILURE);
	}
	unlink(".heredoc.tmp");
	if (dup2(fd_file, STDIN_FILENO) < 0)
	{
		perror("dup2 heredoc");
		exit(EXIT_FAILURE);
	}
	close(fd_file);
}

void	handle_heredoc(t_token *data, t_ast *node, t_params *p, t_env *env)
{
	int				fd_file;
	int				original_stdin;
	t_redirect_file	*heredocs;
	t_list			*heredoc;

	heredoc = data->infiles;
	heredocs = (t_redirect_file *)heredoc->content;
	fd_file = open_heredoc();
	data = (t_token *)(node->data);
	write_heredoc(fd_file, heredocs->value);
	close(fd_file);
	original_stdin = dup(STDIN_FILENO);
	if (original_stdin < 0)
	{
		perror("dup original stdin");
		exit(EXIT_FAILURE);
	}
	fd_file = open(".heredoc.tmp", O_RDONLY);
	set_heredoc_input(fd_file);
	if (data->cmd != NULL)
		execute_node(node, p, env);
	restore_stdin(original_stdin);
	close(original_stdin);
}
