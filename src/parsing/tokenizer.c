/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:19:37 by drestrep          #+#    #+#             */
/*   Updated: 2024/12/07 16:10:36 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * Extracts and tokenizes a segment of the input based on its type,
 * handling quotes and operators. The resulting token is created and
 * added to the lexer.
 */
void	tokenize_strings(t_lexer *lexer, t_token_type type, char **input)
{
	char	*start;
	char	quote;

	start = *input;
	if (type == TOKEN_OUTPUT || type == TOKEN_INPUT)
		(*input)++;
	else if (type == TOKEN_APPEND || type == TOKEN_HEREDOC)
		*input += 2;
	while (**input && **input != '|' && **input != '>' && **input != '<')
	{
		if (**input == '"' || **input == '\'')
		{
			quote = **input;
			(*input)++;
			while (**input && **input != quote)
				(*input)++;
		}
		(*input)++;
	}
	free(lexer->buf);
	lexer->buf = ft_substr(start, 0, *input - start);
	lexer->buf[*input - start] = '\0';
	add_token(&lexer->tokens, create_token(type, lexer->buf));
}

/*
 *	The tokenizer is in charge of separating everything into tokens,
 *	differentiating between operators, redirections and strings.
 */
void	tokenizer(t_lexer *lexer, char **input)
{
	if (**input == '|')
	{
		add_token(&lexer->tokens, create_token(TOKEN_PIPE, "|"));
		(*input)++;
	}
	else if ((**input == '>' && *(*input + 1) != '>') \
			|| (**input == '<' && *(*input + 1) != '<'))
	{
		if (**input == '>')
			tokenize_strings(lexer, TOKEN_OUTPUT, input);
		else
			tokenize_strings(lexer, TOKEN_INPUT, input);
	}
	else if ((**input == '>' && *(*input + 1) == '>') \
			|| (**input == '<' && *(*input + 1) == '<'))
	{
		if (**input == '>')
			tokenize_strings(lexer, TOKEN_APPEND, input);
		else
			tokenize_strings(lexer, TOKEN_HEREDOC, input);
	}
	else
		tokenize_strings(lexer, TOKEN_STRING, input);
}
