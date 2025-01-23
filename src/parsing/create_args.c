/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:13:41 by drestrep          #+#    #+#             */
/*   Updated: 2025/01/23 16:33:35 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//TODO: Este caso falla: export a=" -pepe"

void	find_args(t_token *token, char *str)
{
	char	*aux;
	int		i;
	int		j;

	i = 0;
	j = 1;
	if (str[i] == '"' || str[i] == '\'')
		i = skip_quoted_string(str, i);
	while (is_alnum(str[i]) || str[i] == '-' || str[i] == '|' || \
			str[i] == '"' || str[i] == '\'')
		i++;
	while (str[i] && str[i] != '|')
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			aux = get_quoted_str(str + i, str[i]);
			while (aux[j] == ' ')
				j++;
			if (aux[j] == '-' && !ft_strcmp(token->args, "export"))
				token->flags = append_str(token->flags, aux);
			else
				token->args = append_str(token->args, aux);
			i += ft_strlen(aux);
			free(aux);
		}
		else if (is_alnum(str[i]) || str[i] == '-')
		{
			if (findchar(str + i, ' ') >= 0)
				aux = ft_substr(str + i, 0, findchar(str + i, ' '));
			else
				aux = ft_strdup(str + i);
			if (aux[0] == '-' && !ft_strcmp(token->args, "export"))
				token->flags = append_str(token->flags, aux);
			else
				token->args = append_str(token->args, aux);
			i += ft_strlen(aux);
			free(aux);
		}
		else
			i++;
	}
}

void	get_cmd_flags_and_args(t_token *token, char *full_cmd)
{
	int	i;

	i = 0;
	token->cmd = NULL;
	if (!token->cmd && (full_cmd[i] == '\'' || full_cmd[i] == '"'))
	{
		token->cmd = get_unquoted_str(full_cmd);
		i += ft_strlen(token->cmd);
	}
	if (!token->cmd)
	{
		while (is_alpha(full_cmd[i]) || \
		full_cmd[i] == '_' || full_cmd[i] == '$')
			i++;
		token->cmd = ft_substr(full_cmd, 0, i);
	}
	find_args(token, full_cmd);
}

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

char	*get_args(t_token *token)
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
}

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

void	get_redirection(t_token *token, char *full_cmd)
{
	t_redirect_file	*redirection;
	char			*aux;
	int				j;
	int				i;

	redirection = ft_malloc(sizeof(t_redirect_file));
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
		redirection->value = ft_substr(full_cmd, i, j);
	}
	else
	{
		while (is_alnum(full_cmd[i + j]) \
		|| full_cmd[i + j] == '$' || full_cmd[i + j] == '_')
			j++;
		redirection->value = ft_substr(full_cmd, i, j);
	}
	manage_redirection(token, redirection);
	full_cmd = remove_substr(redirection->value, full_cmd);
}

void	get_redirections(t_token *token)
{
	int	i;

	i = 0;
	while (token->full_cmd[i])
	{
		if (token->full_cmd[i] == '>' || token->full_cmd[i] == '<')
		{
			get_redirection(token, token->full_cmd);
			while (token->full_cmd[i] && token->full_cmd[i] == ' ')
				i++;
		}
		else
			i++;
	}
}

/*
 * Parses a token's value into its components: command, arguments, and flags.
 */
void	get_token_values(t_token *token, char *buf, int space_pos)
{
	(void) buf;
	(void)space_pos;
	if (token->type == 0)
	{
		get_redirections(token);
		get_cmd_flags_and_args(token, token->full_cmd);
	}
}
