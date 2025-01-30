/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection03.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:14:40 by igvisera          #+#    #+#             */
/*   Updated: 2025/01/30 15:17:28 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_output_file(t_redirect_file *outfile)
{
	int	fd;

	fd = open(outfile->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open output");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	redirect_to_files(t_token *data)
{
	int				fd;
	t_redirect_file	*outfile;
	t_list			*outfiles;

	fd = -1;
	outfiles = data->outfiles;
	while (outfiles)
	{
		outfile = (t_redirect_file *)outfiles->content;
		fd = open_output_file(outfile);
		if (outfiles->next)
			close(fd);
		outfiles = outfiles->next;
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 output");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	redirect_output(t_token *data, t_ast *ast, t_params *p, t_env *env)
{
	int	original_stdout;

	original_stdout = dup(STDOUT_FILENO);
	if (original_stdout < 0)
	{
		perror("dup original stdout");
		exit(EXIT_FAILURE);
	}
	redirect_to_files(data);
	execute_node(ast, p, env);
	restore_stdout(original_stdout);
}

void	init_redirct_out(t_ast *ast, t_params *p, t_env *env)
{
	t_token	*token;

	token = (t_token *)(ast->data);
	redirect_output(token, ast, p, env);
}
