/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection03.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:38:07 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/14 17:28:52 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_output_files(t_token *data)
{
	int				fd;
	t_redirect_file	*outfile;
	t_list			*outfiles;

	fd = -1;
	outfiles = data->outfiles;
	while (outfiles)
	{
		outfile = (t_redirect_file *)outfiles->content;
		fd = open(outfile->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("open output");
			exit(EXIT_FAILURE);
		}
		if (outfiles->next)
			close(fd);
		outfiles = outfiles->next;
	}
	return (fd);
}

void	redirect_output(t_ast *ast)
{
	int		fd;
	t_token	*token;

	token = (t_token *)(ast->data);
	fd = open_output_files(token);
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 output");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

char	*path_error(void)
{
	printf("\t--- Error ---\n");
	printf("The env doesnt have PATH use only absolute command\n");
	return (NULL);
}
