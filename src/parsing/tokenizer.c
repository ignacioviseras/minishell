/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:19:37 by drestrep          #+#    #+#             */
/*   Updated: 2024/11/04 02:38:47 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	create_args(t_token *token, char *value, int space_pos)
{
	token->cmd = ft_substr(value, 0, space_pos);
	token->args = ft_strdup(value + space_pos + 1);
	if (!ft_strcmp(token->args, ""))
		token->args = NULL;
	skip_spaces(&token->args);
	token->flags = NULL;
	if (token->args&& *token->args == '-')
	{
		space_pos = ft_charseach(token->args, ' ');
		if (space_pos != 0)
			token->flags = ft_substr(token->args, 0, space_pos);
		else
			token->flags = ft_strdup(token->args);
	}
	
}

/*
 * Creates a new token with the specified type and value, 
 * allocating memory and duplicating the token's value string.
 */
t_token	*create_token(token_type type, char *value)
{
	t_token	*token;
	int		space_pos;

	token = ft_malloc(sizeof(t_token));
	token->cmd_args = ft_strdup(value);
	space_pos = ft_charseach(value, ' ');
	if (space_pos > 0)
		create_args(token, value, space_pos);
	else
	{
		token->cmd = ft_strdup(value);
		token->args = NULL;
		token->flags = NULL;
	}
	token->type = type;
	token->next = NULL;
	return (token);
}

/*
 * Adds a new token to the end of the token list. 
 * If the list is empty, the new token becomes the head.
 */
void	add_token(t_token **head, t_token *new_token)
{
	t_token	*temp;

	if (*head == NULL)
		*head = new_token;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
}

/*
 * Tokenizes strings based on quotes or delimiters. 
 * If the input starts with a quote (' or "), it extracts the quoted string. 
 * Otherwise, it tokenizes until encountering a space or operator (|, >, <). 
 */
void	tokenize_strings(t_lexer *lexer, char **input)
{
	char	quote;
	char	*start;

	start = *input;
	while (**input && **input != '|' \
		&& **input != '>' && **input != '<')
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
    strncpy(lexer->buf, start, *input - start);
    lexer->buf[*input - start] = '\0';
	add_token(&lexer->tokens, create_token(TOKEN_STRING, lexer->buf));
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
	else if ((**input == '>' && *(*input + 1) != '>') || (**input == '<' && *(*input + 1) != '<'))
	{
		if (**input == '>')
			add_token(&lexer->tokens, create_token(TOKEN_OUTPUT, ">"));
		else
			add_token(&lexer->tokens, create_token(TOKEN_INPUT, "<"));
		(*input)++;
	}
	else if ((**input == '>' && *(*input + 1) == '>') || (**input == '<' && *(*input + 1) == '<'))
	{
		if (**input == '>')
			add_token(&lexer->tokens, create_token(TOKEN_APPEND, ">>"));
		else
			add_token(&lexer->tokens, create_token(TOKEN_HEREDOC, "<<"));
		*input += 2;
	}
	else
		tokenize_strings(lexer, input);
}
