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

void	redirect_output(t_token *data, t_ast *ast, t_params *p, t_env *env)
{
	pid_t	pid;
	int		fd;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		fd = open_output_files(data);
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			perror("dup2 output");
			close(fd);
			exit(EXIT_FAILURE);
		}
		close(fd);
		execute_node(ast, p, env);
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(pid, &p->status, 0);
}

void	init_redirct_out(t_ast *ast, t_params *p, t_env *env)
{
	t_token	*token;

	token = (t_token *)(ast->data);
	redirect_output(token, ast, p, env);
}

char	*path_error(void)
{
	printf("\t--- Error ---\n");
	printf("The env doesnt have PATH use only absolute command\n");
	return (NULL);
}
