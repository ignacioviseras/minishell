/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:13:41 by drestrep          #+#    #+#             */
/*   Updated: 2025/01/27 14:55:30 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_redirection(char *str, int i)
{
	if ((str[i] == '>' && str[i + 1] != '>') || \
		(str[i] == '<' && str[i + 1] != '<'))
		return (1);
	else if ((str[i] == '>' && str[i + 1] == '>') || \
		(str[i] == '<' && str[i + 1] == '<'))
		return (2);
	else
		return (0);
}

/* char	*get_args(t_token *token)
{
	int		i;
	int		redirect;
	char	*args;

	i = 0;
	args = NULL;
	while (token->full_cmd[i])
	{
		redirect = is_redirection(token->full_cmd, i);
		if (redirect > 0)
		{
			i += redirect;
			find_args(token, token->full_cmd);
		}
		i++;
	}
	return (args);
} */

void	manage_redirection(t_token *token, t_redirect_file *redirection)
{
	t_list			*new_node;

	new_node = ft_malloc(sizeof(t_list));
	if (redirection->value[0] == '>')
	{
		new_node->content = redirection;
		new_node->next = NULL;
		ft_lstadd_back(&token->outfiles, new_node);
		if (redirection->value[1] == '>')
			redirection->type = APPEND;
		else
			redirection->type = WRITE;
	}
	else if (redirection->value[0] == '<')
	{
		new_node->content = redirection;
		new_node->next = NULL;
		ft_lstadd_back(&token->infiles, new_node);
		if (redirection->value[1] == '<')
			redirection->type = HEREDOC;
		else
			redirection->type = INFILE;
	}
}

void	get_redirection(t_redirect_file *redir, char *full_cmd)
{
	char			*aux;
	int				j;
	int				i;

	i = 0;
	while (is_redirection(full_cmd, i) == 0)
		i++;
	j = is_redirection(full_cmd, i);
	while (full_cmd[i + j] == ' ')
		j++;
	if (full_cmd[i + j] == '\'' || full_cmd[i + j] == '"')
	{
		aux = get_quoted_str(full_cmd + i + j, full_cmd[i + j]);
		j += ft_strlen(aux);
		free(aux);
		redir->value = ft_substr(full_cmd, i, j);
	}
	else
	{
		while (is_alnum(full_cmd[i + j]) \
		|| full_cmd[i + j] == '$' || full_cmd[i + j] == '_')
			j++;
		redir->value = ft_substr(full_cmd, i, j);
	}
}

void	get_redirections(t_token *token)
{
	t_redirect_file	*redir;
	int				i;

	i = 0;
	redir = ft_malloc(sizeof(t_redirect_file));
	while (token->full_cmd[i])
	{
		if (token->full_cmd[i] == '>' || token->full_cmd[i] == '<')
		{
			get_redirection(redir, token->full_cmd);
			manage_redirection(token, redir);
			token->full_cmd = remove_substr(redir->value, token->full_cmd);
			while (token->full_cmd[i] && token->full_cmd[i] == ' ')
				i++;
		}
		else
			i++;
	}
}
