/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:13:41 by drestrep          #+#    #+#             */
/*   Updated: 2025/01/03 13:10:03 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


//TODO ESTO A LA MIERDA :DDDDD
/* void	handle_quoted_argument(t_token *token, char **buf)
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
} */


char	*find_args(char *str, int *i)
{
	skip_input_spaces(&str + *i); //idk if this is okay
	if (str[*i] == '"' || str[*i] == '\'')
			*i = skip_quoted_string(str, i);
	while (is_alnum(str[*i]) || str[*i] == '-' || str[*i] == '|')
		(*i)++;
	while (str[*i] && str[*i] != '|')
	{
		if (str[*i] == '"' || str[*i] == '\'')
			return (get_quoted_str(str + *i, str[*i]));
		if (is_alnum(str[*i]) || str[*i] == '-')
		{
			if (findchar(str + *i, ' ') >= 0 )
				return (ft_substr(str + *i, 0, findchar(str + *i, ' ')));
			else if (findchar(str + *i, ' ') >= 0 && findchar(str + *i, '|') >= 0 \
				&& findchar(str + *i, ' ') < findchar(str + *i, '|'))
				return ("EY");
			/* else
				args; */
		}
		(*i)++;
	}
	return (NULL);
}

int	ft_is_redirection(char *str, int i)
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
	
	i = ft_strlen(token->cmd);
	while (token->full_cmd[i])
	{
		redirect = ft_is_redirection(token->full_cmd, i);
		if (redirect > 0)
		{
			i += redirect;
			args = find_args(token->full_cmd, &i);
		}
		i++;
	}
}

/*
 * Parses a token's value into its components: command, arguments, and flags.
 */
void	create_args(t_token *token, char *buf, int space_pos)
{
	token->cmd = ft_substr(buf, 0, space_pos);
	/* if (token->type > 1)
		create_redirection_args(token, buf);
	else */
	printf("%s\n", token->full_cmd);
	exit(0);
	token->flags = NULL;
	token->args = get_args(token);
	token->args = ft_strdup(buf + space_pos + 1);
	if (!ft_strcmp(token->args, ""))
		token->args = NULL;
	token->args = skip_args_spaces(token->args);
	if (token->args && *token->args == '-')
		token->flags = get_all_flags(token->args, \
		token->flags, token->type);
}
