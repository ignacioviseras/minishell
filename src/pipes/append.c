/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:58:28 by igvisera          #+#    #+#             */
/*   Updated: 2025/03/14 17:40:27 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_append_files(t_token *data)
{
	int				fd;
	t_list			*current;
	t_redirect_file	*outfile;

	fd = -1;
	current = data->redir;
	int	i = 0;
	while (current)
	{
		outfile = (t_redirect_file *)current->content;
		printf("%d: %s\n", i, outfile->value);
		if (outfile->type == INFILE)
			break ;
		fd = open(outfile->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			perror("open append");
			return (-1);
		}
		if (current->next)
			close(fd);
		current = current->next;
	}
	return (fd);
}

int	redirect_append(t_ast *ast)
{
	int				fd;
	t_token			*token;
	t_list			*list;
	t_redirect_file	*append;

	token = (t_token *)(ast->data);
	fd = open_append_files(token);
	if (fd == -1)
	{
		g_exit_status = 1;
		return (-1);
	}
	list = (t_list *)token->redir;
	append = (t_redirect_file *)list->content;
	while (list->next && append->type != HEREDOC)
	{
		list = list->next;
		append = (t_redirect_file *)list->content;
	}
	//TODO: AQUÍ ESTÁ EL PROBLEMA
	if (dup2(fd, STDOUT_FILENO) < 0 && compare_strings(append->value,".heredoc.tmp") == 0)
	{
		printf("Value: %s\n", append->value);
		perror("dup2 append");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
	return (0);
}
