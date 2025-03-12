/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:03:53 by igvisera          #+#    #+#             */
/*   Updated: 2025/03/10 17:35:01 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_input_files(t_token *data)
{
	int				fd;
	t_redirect_file	*infile;
	t_list			*infiles;

	fd = -1;
	infiles = data->infiles;
	while (infiles)
	{
		infile = (t_redirect_file *)infiles->content;
		fd = open(infile->value, O_RDONLY);
		if (fd < 0)
		{
			g_exit_status = 1;
			perror("open input");
			return (-1);
		}
		if (ft_strncmp(infile->value, ".heredoc.tmp", 12) == 0)
			unlink(infile->value);
		if (infiles->next)
			close(fd);
		infiles = infiles->next;
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
