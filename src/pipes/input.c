/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:03:53 by igvisera          #+#    #+#             */
/*   Updated: 2025/03/12 19:04:51 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_input_files(t_token *data)
{
	int				fd;
	int				temp_fd;
	t_list			*current;
	t_redirect_file	*infile;

	fd = -1;
	current = data->infiles;
	while (current)
	{
		infile = (t_redirect_file *)current->content;
		temp_fd = open(infile->value, O_RDONLY);
		if (temp_fd < 0)
		{
			g_exit_status = 1;
			perror("open input");
			return (-1);
		}
		if (fd != -1)
			close(fd);
		fd = temp_fd;
		current = current->next;
		if (infile && ft_strncmp(infile->value, ".heredoc.tmp", 12) == 0)
			unlink(infile->value);
	}
	return (fd);
}

int	redirect_input(t_ast *ast)
{
	int		fd;
	t_token	*token;

	token = (t_token *)(ast->data);
	fd = open_input_files(token);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2 input");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
	return (0);
}
