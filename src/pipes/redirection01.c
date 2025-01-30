/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:03:53 by igvisera          #+#    #+#             */
/*   Updated: 2025/01/30 15:17:52 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_input_file(t_redirect_file *infile)
{
	int	fd;

	fd = open(infile->value, O_RDONLY);
	if (fd < 0)
	{
		perror("open input");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	redirect_from_files(t_token *data)
{
	int				fd;
	t_redirect_file	*infile;
	t_list			*infiles;

	fd = -1;
	infiles = data->infiles;
	while (infiles)
	{
		infile = (t_redirect_file *)infiles->content;
		fd = open_input_file(infile);
		if (infiles->next)
			close(fd);
		infiles = infiles->next;
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2 input");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	redirect_input(t_token *data, t_ast *ast, t_params *p, t_env *env)
{
	int	original_stdin;

	original_stdin = dup(STDIN_FILENO);
	if (original_stdin < 0)
	{
		perror("dup original stdin");
		exit(EXIT_FAILURE);
	}
	redirect_from_files(data);
	execute_node(ast, p, env);
	restore_stdin(original_stdin);
}

void	init_redirct_in(t_ast *ast, t_params *p, t_env *env)
{
	t_token	*token;

	token = (t_token *)(ast->data);
	redirect_input(token, ast, p, env);
}
