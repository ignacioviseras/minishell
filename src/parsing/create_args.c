/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:13:41 by drestrep          #+#    #+#             */
/*   Updated: 2024/12/10 14:47:54 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_quoted_argument(t_token *token, char **buf)
{
	char	quote;

	token->args = get_quoted_str(*buf, **buf);
	quote = **buf;
	while (**buf != quote)
		(*buf)++;
	token->flags = get_all_flags(token->full_cmd, \
	token->flags, token->type);
}

void	handle_space_separated_argument(t_token *token, char **buf)
{
	token->args = ft_substr(*buf, 0, findchar(*buf, ' '));
	*buf += findchar(*buf, ' ');
	while (**buf && **buf == ' ')
		(*buf)++;
	token->flags = ft_strdup(*buf);
	free(token->full_cmd);
	token->full_cmd = ft_strjoin(token->cmd, token->args);
}

void	handle_default_argument(t_token *token, char *buf)
{
	token->args = ft_strdup(buf);
	token->flags = NULL;
}

void	create_redirection_args(t_token *token, char *buf)
{
	skip_input_spaces(&buf);
	while (*buf && !is_alnum(*buf) && *buf != '-' && \
			*buf != '"' && *buf != '\'')
		buf++;
	if ((findchar(buf, '"') >= 0 && (findchar(buf, '"') < findchar(buf, ' '))) \
	|| (findchar(buf, '\'') >= 0 && (findchar(buf, '\'') < findchar(buf, ' '))))
		handle_quoted_argument(token, &buf);
	else if (findchar(buf, ' ') > 0)
		handle_space_separated_argument(token, &buf);
	else
		handle_default_argument(token, buf);
}

/*
 * Parses a token's value into its components: command, arguments, and flags.
 */
void	create_args(t_token *token, char *buf, int space_pos)
{
	token->cmd = ft_substr(buf, 0, space_pos);
	if (token->type > 1)
		create_redirection_args(token, buf);
	else
	{
		token->flags = NULL;
		token->args = ft_strdup(buf + space_pos + 1);
		if (!ft_strcmp(token->args, ""))
			token->args = NULL;
		token->args = skip_args_spaces(token->args);
		if (token->args && *token->args == '-')
			token->flags = get_all_flags(token->args, \
			token->flags, token->type);
	}
}
