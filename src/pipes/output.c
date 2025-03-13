/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:38:07 by igvisera          #+#    #+#             */
/*   Updated: 2025/03/13 15:47:12 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_output_files(t_token *data)
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
		fd = open(outfile->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			g_exit_status = 1;
			perror("open output");
			return (-1);
		}
		if (outfiles->next)
			close(fd);
		outfiles = outfiles->next;
	}
	return (fd);
}

int	redirect_output(t_ast *ast)
{
	int		fd;
	t_token	*token;

	token = (t_token *)(ast->data);
	fd = open_output_files(token);
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 output");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

char	*path_error(void)
{
	printf("\t--- Error ---\n");
	printf("The env doesnt have PATH use only absolute command\n");
	return (NULL);
}
