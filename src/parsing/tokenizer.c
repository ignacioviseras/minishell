/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:19:37 by drestrep          #+#    #+#             */
/*   Updated: 2025/01/22 17:50:52 by drestrep         ###   ########.fr       */
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
	while (**input && **input != '|')
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
	else
		tokenize_strings(lexer, TOKEN_STRING, input);
}
