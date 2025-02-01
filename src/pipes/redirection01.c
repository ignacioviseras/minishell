/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:03:53 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/01 17:56:59 by igvisera         ###   ########.fr       */
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
			perror("open input");
			exit(EXIT_FAILURE);
		}
		if (infiles->next)
			close(fd);
		infiles = infiles->next;
	}
	return (fd);
}

void	redirect_input(t_token *data, t_ast *ast, t_params *p, t_env *env)
{
	int	fd;
	int	original_stdin;

	original_stdin = dup(STDIN_FILENO);
	if (original_stdin < 0)
	{
		perror("dup original stdin");
		exit(EXIT_FAILURE);
	}
	fd = open_input_files(data);
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2 input");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
	execute_node(ast, p, env);
	restore_stdin(original_stdin);
	close(original_stdin);
}

void	init_redirct_in(t_ast *ast, t_params *p, t_env *env)
{
	t_token	*token;

	token = (t_token *)(ast->data);
	redirect_input(token, ast, p, env);
}
