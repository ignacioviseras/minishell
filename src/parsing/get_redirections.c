/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:13:41 by drestrep          #+#    #+#             */
/*   Updated: 2025/01/28 19:47:08 by drestrep         ###   ########.fr       */
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

void	classify_redirection(t_token *token, t_redirect_file *redir)
{
	t_list			*new_node;

	new_node = ft_malloc(sizeof(t_list));
	if (redir->value[0] == '>')
	{
		new_node->content = redir;
		new_node->next = NULL;
		ft_lstadd_back(&token->outfiles, new_node);
		if (redir->value[1] == '>')
			redir->type = APPEND;
		else
			redir->type = WRITE;
	}
	else if (redir->value[0] == '<')
	{
		new_node->content = redir;
		new_node->next = NULL;
		ft_lstadd_back(&token->infiles, new_node);
		if (redir->value[1] == '<')
			redir->type = HEREDOC;
		else
			redir->type = INFILE;
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
		while (full_cmd[i + j] && valid_char_filename(full_cmd[i + j]))
			j++;
		redir->value = ft_substr(full_cmd, i, j);
	}
}

char	*remove_redirection_operators(char *str)
{
	char	*new_redir;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (!valid_char_filename(str[i]))
		i++;
	new_redir = ft_malloc((ft_strlen(str + i) + 1) * sizeof(char));
	while (str[i])
		new_redir[j++] = str[i++];
	new_redir[j] = '\0';
	free(str);
	return (new_redir);
}

void	get_redirections(t_token *token)
{
	t_redirect_file	*redir;
	int				i;

	i = 0;
	while (token->full_cmd[i])
	{
		if (token->full_cmd[i] == '\'' || token->full_cmd[i] == '"')
			i = skip_quoted_string(token->full_cmd, i);
		else if (token->full_cmd[i] == '>' || token->full_cmd[i] == '<')
		{
			redir = ft_malloc(sizeof(t_redirect_file));
			get_redirection(redir, token->full_cmd);
			classify_redirection(token, redir);
			token->full_cmd = remove_substr(redir->value, token->full_cmd);
			redir->value = remove_redirection_operators(redir->value);
			while (token->full_cmd[i] && token->full_cmd[i] == ' ')
				i++;
		}
		else
			i++;
	}
}
