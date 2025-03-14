/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:03:53 by igvisera          #+#    #+#             */
/*   Updated: 2025/03/14 18:02:03 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	compare_strings(char *value, char *heredoc)
{
	char	*aux;

	aux = value;
	if (value[0] != '.')
		return (0);
	while (heredoc && *heredoc == *value)
	{
		heredoc++;
		value++;
	}
	value = aux;
	if (!heredoc)
		return (0);
	return (1);
}

int	open_input_files(t_token *data)
{
	int				fd;
	int				temp_fd;
	t_list			*current;
	t_redirect_file	*infile;

	fd = -1;
	current = data->redir;
	while (current)
	{
		infile = (t_redirect_file *)current->content;
		temp_fd = open(infile->value, O_RDONLY);
		printf("input_file '%s', fd'%d'\n", infile->value, temp_fd);
		if (temp_fd < 0)
			return (-1);
		if (fd != -1)
			close(fd);
		fd = temp_fd;
		current = current->next;
		if (infile && ft_strncmp(infile->value, ".heredoc.tmp", 12) == 0)
			unlink(infile->value);
	}
	return (fd);
}

int	redirect_input(t_ast *ast)
{
	int				fd;
	t_token			*token;
	t_list			*list;
	t_redirect_file	*infile;

	token = (t_token *)(ast->data);
	list = (t_list *)token->redir;
	infile = (t_redirect_file *)list->content;
	fd = open_input_files(token);
	if (fd == -1 && compare_strings(infile->value, ".heredoc.tmp") == 0)
	{
		g_exit_status = 1;
		perror("open input");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) < 0 && \
	compare_strings(infile->value, ".heredoc.tmp") == 0)
	{
		perror("dup2 input");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
	return (0);
}
