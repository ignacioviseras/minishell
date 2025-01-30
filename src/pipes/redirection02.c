/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:58:28 by igvisera          #+#    #+#             */
/*   Updated: 2025/01/30 15:15:07 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_append_file(t_redirect_file *outfile)
{
	int	fd;

	fd = open(outfile->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open append");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	redirect_to_append_files(t_token *data)
{
	int				fd;
	t_redirect_file	*outfile;
	t_list			*outfiles;

	fd = -1;
	outfiles = data->outfiles;
	while (outfiles)
	{
		outfile = (t_redirect_file *)outfiles->content;
		fd = open_append_file(outfile);
		if (outfiles->next)
			close(fd);
		outfiles = outfiles->next;
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 append");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	redirect_append(t_token *data, t_ast *ast, t_params *p, t_env *env)
{
	int	original_stdout;

	original_stdout = dup(STDOUT_FILENO);
	if (original_stdout < 0)
	{
		perror("dup original stdout");
		exit(EXIT_FAILURE);
	}
	redirect_to_append_files(data);
	execute_node(ast, p, env);
	restore_stdout(original_stdout);
}

void	init_redritect_append(t_ast *ast, t_params *p, t_env *env)
{
	t_token	*token;

	token = (t_token *)(ast->data);
	redirect_append(token, ast, p, env);
}
