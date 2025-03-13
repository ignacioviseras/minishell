/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:58:28 by igvisera          #+#    #+#             */
/*   Updated: 2025/03/13 15:46:37 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_append_files(t_token *data)
{
	int				fd;
	t_redirect_file	*outfile;
	t_list			*outfiles;

	fd = -1;
	outfiles = data->redir;
	while (outfiles)
	{
		outfile = (t_redirect_file *)outfiles->content;
		if (outfile->type == INFILE)
			break ;
		fd = open(outfile->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			perror("open append");
			return (-1);
		}
		if (outfiles->next)
			close(fd);
		outfiles = outfiles->next;
	}
	return (fd);
}

int	redirect_append(t_ast *ast)
{
	t_token	*token;
	int		fd;

	token = (t_token *)(ast->data);
	fd = open_append_files(token);
	if (fd == -1)
	{
		g_exit_status = 1;
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 append");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
	return (0);
}
